//
//  aggregator.hpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/7.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#ifndef aggregator_hpp
#define aggregator_hpp
#include "util/file.hpp"
#include <stdio.h>

class aggregator{
public:
    ~aggregator();
    aggregator(file* _input_file);
    void aggregate();
private:
    file* input_file;
};


#endif /* aggregator_hpp */
