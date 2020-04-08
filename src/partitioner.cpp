//
//  patitioner.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/4.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "partitioner.hpp"
#include "common/constant.hpp"
#include <stdio.h>
#include <vector>
#include <iostream>
#include "util/logger.hpp"


range::range(int64_t _from, int64_t _to):from(_from),to(_to){}

partitioner::partitioner(file* _input_file):input_file(_input_file){
    slices.clear();
    ranges.clear();
}

partitioner::partitioner(file* _input_file, statistic* _stat):input_file(_input_file), stat(_stat){
    slices.clear();
    ranges.clear();
}

partitioner::~partitioner(){
    for(file* s: slices){
        delete s;
    }
}



int partitioner::hash_partition(int num,int level){
    range_partition(num);
    std::vector<file*> slices_empty;
    //create empty slices
    for(int i=0;i<num;i++){
        file* si = new file(input_file->get_path()+"_"+std::to_string(i));
        slices_empty.push_back(si);
        si->create_file();
    }
    // create a hash function h
    std::hash<std::string> h;
    //get disk data into memory block by block according to ranges
    for(auto r: ranges){
        logger("Read file "+input_file->get_path()+". address: "+"[" +std::to_string(r.from) +","+std::to_string(r.to) +")");
        int64_t pos = r.from;
        int block_bytes = int(r.to-r.from);
        std::map<std::string, int64_t> agg = input_file->get_agg(pos,block_bytes);
        // agg_partition[i] stores agg will write to disk on partition i
        std::vector<std::map<std::string, int64_t>> agg_partition;
        for(auto tuple: agg){
            if(stat != NULL && stat->sampled()){
                stat->add_cnt(tuple);
            }
            else{
                size_t hash_number = h(tuple.first);
                if(level > 0){
                    std::hash<size_t>h2;
                    for(int i=0;i<level;i++){
                        hash_number = h2(hash_number);
                    }
                }
                int partition_number = hash_number%num;
                agg_partition[partition_number].insert(tuple);
            }
        }
        logger("finish add agg to partition.");
        
        std::map<std::string, int64_t>().swap(agg);
        logger("finish release agg.");
        
        for(int i=0;i<num;i++){
            logger("Write file "+ slices_empty[i]->get_path());
            logger(std::to_string(agg_partition[i].size()));
            slices_empty[i]->write_agg(agg_partition[i]);
        }
        logger("finish write to disk.");
    }
    if(stat != NULL && stat->sampled()){
        stat->set_sample_all_collected();
    }
    //Check if slice file is empty file
    //if empty delete this slice
    slices.clear();
    for(int i=0;i<num;i++){
        if(slices_empty[i]->is_empty()){
            slices_empty[i]->remove_file();
        }
        else{
            slices.push_back(slices_empty[i]);
        }
    }
    // delete file to save disk space. (because I have only 230GB free disk on my own laptop)
    input_file->remove_file();
    delete input_file;
    input_file = NULL;
    return slices.size();
}

std::vector<range> partitioner::get_ranges(){
    return ranges;
}

std::vector<file*> partitioner::get_slices(){
    return slices;
}


int partitioner::range_partition(int num){
    int64_t length = input_file->filesize();
    int64_t range_num = length/num;
    ranges.clear();
    std::vector<int64_t> splits;
    splits.clear();
    splits.push_back(0);
    for(int i=0;i<num;i++){
        // split file into blocks with range [i*range_num, (i+1)*range_num)
        // but this split will also splits url, so call get_next_url_pos((i+1)*range_num)
        if(i == num-1){
            splits.push_back(length);
        }
        else{
            splits.push_back(input_file->get_next_line_pos((i+1)*range_num));
        }
    }
    splits.erase(unique(splits.begin(), splits.end()), splits.end());
    for(int i=0;i<splits.size()-1;i++){
        ranges.push_back(range(splits[i],splits[i+1]));
    }
    return splits.size()-1;
}
