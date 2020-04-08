//
//  runner.hpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/8.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#ifndef runner_hpp
#define runner_hpp

#include <stdio.h>
#include "util/file.hpp"
#include "statistic.hpp"
#include "partitioner.hpp"

class runner{
public:
    ~runner();
    runner(file* _input_file, file* _out_file);
    void run();
private:
    void run_recursive(partitioner& p,int level);
    file* input_file;
    file* out_file;
    statistic* stat;
};

#endif /* runner_hpp */
