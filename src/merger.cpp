//
//  merger.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/7.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "merger.hpp"
#include "util/logger.hpp"



merger::merger(file* _input_file, statistic* _stat):input_file(_input_file),stat(_stat){}

merger::~merger(){}

bool merger::merge(){
    if(int64_t(input_file->filesize()) > AGGREGATE_BYTES){
        logger("file size too large, cannot do merge in memory, please repartition or aggregate.");
        return false;
    }
    std::map<std::string, int64_t> agg = input_file->get_file_agg();
    stat->merge_agg_into_topk(agg);
    return true;
}
