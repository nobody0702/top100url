//
//  aggregator.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/7.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "aggregator.hpp"
#include "util/file.hpp"
#include "common/constant.hpp"
#include "partitioner.hpp"
#include "logger.hpp"


aggregator::aggregator(file* _input_file):input_file(_input_file){}

aggregator::~aggregator(){}



int upper_num(int64_t size, int64_t bytes){
    return (size%bytes == 0) ? (size/bytes) : (size/bytes + 1);
}

void aggregator::aggregate(){
    partitioner p(input_file);
    std::string outfile_name = input_file->get_path()+"_tmp";
    file outf(outfile_name);
    outf.create_file();
    int num_p = upper_num(int64_t(input_file->filesize()),AGGREGATE_BYTES);
    p.range_partition(num_p);
    auto ranges = p.get_ranges();
    //for each range, do agg
    for(auto r: ranges){
        logger("Read file "+input_file->get_path()+". address: "+"[" +std::to_string(r.from) +","+std::to_string(r.to) +")");
        int64_t pos = r.from;
        int block_bytes = int(r.to-r.from);
        std::map<std::string, int64_t> agg = input_file->get_agg(pos,block_bytes);;
        outf.write_agg(agg);
    }
    input_file->mv_replace(outfile_name);
}


