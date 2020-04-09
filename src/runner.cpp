//
//  runner.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/8.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "runner.hpp"
#include "common/constant.hpp"
#include "merger.hpp"
#include "aggregator.hpp"
#include "util/logger.hpp"


runner::runner(file* _input_file, file* _out_file):input_file(_input_file),out_file(_out_file){
    stat = new statistic(input_file, 100);
}

runner::~runner(){
    delete stat;
    stat = NULL;
}


int upper_div(int64_t t1, int64_t t2){
    if(t1%t2 == 0) return t1/t2;
    else {return (t1/t2)+1;}
}

void runner::run_recursive(partitioner& p,int level){
    for(file* s: p.get_slices()){
        if(s->filesize() < AGGREGATE_BYTES){
            logger("merge file: "+s->get_path());
            merger m(s, stat);
            m.merge();
        }
        else{
            int64_t size_before,size_after;
            do{
                logger("aggregate file: "+s->get_path());
                size_before = s->filesize();
                aggregator a(s);
                a.aggregate(upper_div(size_before,AGGREGATE_BYTES));
                size_after = s->filesize();
            }
            while(size_after < size_before);
            if(s->filesize() < AGGREGATE_BYTES){
                logger("merge file: "+s->get_path());
                merger m(s, stat);
                m.merge();
                continue;
            }
            logger("repartition file: "+s->get_path());
            // if aggregator doesn't work, then repartition
            partitioner p_next(s);
            p_next.hash_partition(upper_div(s->filesize(),AGGREGATE_BYTES),level);
            run_recursive(p_next,level+1);
        }
    }
}


void runner::run(){
    logger("start run");
    logger("collect sample");
    stat->collect_sample(100*10000);
    logger("hash partition");
    partitioner p(input_file,stat);
    p.hash_partition(upper_div(input_file->filesize(),AGGREGATE_BYTES), 0);
    logger("merge sample into topk");
    if(stat->sample_all_collected()){
       stat->merge_sample_into_topk();
    }
    logger("run recursive");
    run_recursive(p,1);
    logger("output result.");
    stat->output_topk(out_file);
    logger("finished");
}
