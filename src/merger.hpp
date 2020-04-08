//
//  merger.hpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/7.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#ifndef merger_hpp
#define merger_hpp

#include <stdio.h>
#include "statistic.hpp"
#include "util/file.hpp"


class merger{
public:
    ~merger();
    merger(file* _input_file, statistic* _stat);
    bool merge();
private:
    file* input_file;
    statistic* stat;
};

#endif /* merger_hpp */
