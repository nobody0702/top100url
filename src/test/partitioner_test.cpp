//
//  partitioner_test.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/6.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include <stdio.h>
#include <boost/test/unit_test.hpp>
#include "../util/file.hpp"
#include "../partitioner.hpp"
#include "../common/constant.hpp"

bool cmp_ranges(std::vector<range> r1,std::vector<range> r2){
    if(r1.size() != r2.size())return false;
    for(int i=0;i<r1.size();i++){
        if(r1[i].from != r2[i].from) return false;
        if(r1[i].to != r2[i].to) return false;
    }
    return true;
}


BOOST_AUTO_TEST_SUITE(partitioner_tests)

BOOST_AUTO_TEST_CASE(partitioner_testrange_partition){
    clock_t start = clock();
    file f(INPUT_FILE_TEST);
    partitioner p(&f);
    p.range_partition(3);
    std::vector<range> testr;
    testr.push_back(range(0,180));
    testr.push_back(range(180,346));
    testr.push_back(range(346,515));
    BOOST_CHECK(cmp_ranges(p.get_ranges(), testr));
}

BOOST_AUTO_TEST_SUITE_END()
