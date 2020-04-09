//
//  runner_test.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/9.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//



#include <stdio.h>
#include <boost/test/unit_test.hpp>
#include "../runner.hpp"
#include "../common/constant.hpp"
#include "../util/file.hpp"


BOOST_AUTO_TEST_SUITE(runner_tests)


BOOST_AUTO_TEST_CASE(runner_testrun){
    file in(INPUT_FILE);
    file out(OUTPUT_FILE);
    runner r(&in,&out);
    r.run();
}


BOOST_AUTO_TEST_SUITE_END()
