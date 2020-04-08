//
//  patitioner.hpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/4.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#ifndef partitioner_hpp
#define partitioner_hpp
#include <stdio.h>
#include <string.h>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include "util/file.hpp"
#include "statistic.hpp"


//define a bytes range [from,to) in file system
struct range{
    int64_t from;
    int64_t to;
    range(int64_t _from, int64_t _to);
};


class partitioner{
public:
    ~partitioner();
    partitioner(file* _input_file);
    partitioner(file* _input_file, statistic* _stat);
    int hash_partition(int num, int level);
    int range_partition(int num);
    std::vector<range> get_ranges();
    std::vector<file*> get_slices();
private:
    file* input_file;
    //partition files name vector
    std::vector<file*> slices;
    //store ranges
    std::vector<range> ranges;
    statistic* stat = NULL;
};

#endif /* patitioner_hpp */
