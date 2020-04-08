//
//  file_test.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/5.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "../util/file.hpp"
#include "../common/constant.hpp"
#include <boost/test/unit_test.hpp>



BOOST_AUTO_TEST_SUITE(file_tests)

BOOST_AUTO_TEST_CASE(file_testread_file){
    file f(INPUT_FILE_TEST);

    BOOST_CHECK(f.get_next_line(0) == "ftp://x3L7.QFjKX:737:02/E4bZ");
    BOOST_CHECK(f.get_next_line(1) == "http://657.627.039.991:3:5//d/");
    BOOST_CHECK(f.get_next_line(28) == "http://657.627.039.991:3:5//d/");
    BOOST_CHECK(f.get_next_line(29) == "https://713D.eklAI:1:78:3:153/ABAV");
    BOOST_CHECK(f.get_next_line(24) == "http://657.627.039.991:3:5//d/");
    BOOST_CHECK(f.get_next_line((int64_t)f.filesize()-1) == "");
    BOOST_CHECK(f.get_next_line((int64_t)f.filesize()-2) == "");
    BOOST_CHECK(f.get_next_line((int64_t)f.filesize()-3) == "");
    BOOST_CHECK(f.get_string((int64_t)f.filesize()-3,1) == "0");
    BOOST_CHECK(f.get_string((int64_t)f.filesize()-3,2) == "03");
    BOOST_CHECK(f.get_string((int64_t)f.filesize(),2) == "");
    BOOST_CHECK(f.get_string(0,4) == "ftp:");
    BOOST_CHECK(f.get_string(33,34) == "://657.627.039.991:3:5//d/\nhttps:/");
    BOOST_CHECK(f.get_this_line(3) == "://x3L7.QFjKX:737:02/E4bZ");
    BOOST_CHECK(f.get_this_line((int64_t)f.filesize()-3) == "03");
    BOOST_CHECK(f.get_this_line(33) == "://657.627.039.991:3:5//d/");
}


BOOST_AUTO_TEST_CASE(file_testwrite_file){
    /*file fw(WRITE_FILE_TEST);
    fw.write_str_on_end("https://774.491.555.829:0:48:8306\n");*/
}

BOOST_AUTO_TEST_SUITE_END()






