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
#include "../util/logger.hpp"


BOOST_AUTO_TEST_SUITE(runner_tests)


BOOST_AUTO_TEST_CASE(runner_testrun){
    /*clock_t start = clock();
    file in(INPUT_FILE);
    file out(OUTPUT_FILE);
    runner r(&in,&out);
    r.run();
    logger(std::to_string((clock() - start) * 1.0 / CLOCKS_PER_SEC * 1000));*/
}


BOOST_AUTO_TEST_SUITE_END()
