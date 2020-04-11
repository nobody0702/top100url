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

bool cmp_agg(std::unordered_map<std::string, int64_t> agg1, std::unordered_map<std::string, int64_t> agg2){
    if(agg1.size() != agg2.size()) return false;
    for(auto tuple: agg1){
        if(agg2[tuple.first] != tuple.second) return false;
    }
    return true;
}

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
    file f1(INPUT_FILE_AGG_1);
    std::unordered_map<std::string,int64_t> agg_cmp;
    agg_cmp["http://917.554.188.352:678:1/G"] = 2;
    agg_cmp["https://774.491.555.829:0:48:8306"] = 1;
    agg_cmp["https://713D.eklAI:1:78:3:153/ABAV"] = 1;
    agg_cmp["http://657.627.039.991:3:5//d/"] = 1;
    agg_cmp["http://2W.htAZh:9:4075:50:4/QA_"] = 1;
    std::unordered_map<std::string,int64_t> agg = f1.get_agg(29, 200);
    BOOST_CHECK(cmp_agg(agg,agg_cmp));
    file f2(INPUT_FILE_AGG_2);
    std::unordered_map<std::string,int64_t> agg2 = f2.get_agg(31, 200);
    std::unordered_map<std::string,int64_t> agg_cmp2;
    agg_cmp2["http://917.554.188.352:678:1/G"] = 2;
    agg_cmp2["https://713D.eklAI:1:78:3:153/ABAV"] = 4;
    agg_cmp2["http://657.627.039.991:3:5//d/"] = 1;
    agg_cmp2["http://2W.htAZh:9:4075:50:4/QA_"] = 2;
    agg_cmp2["https://774.491.555.829:0:48:8306"] = 3;
    BOOST_CHECK(cmp_agg(agg2,agg_cmp2));
}


BOOST_AUTO_TEST_CASE(file_testwrite_file){
    file fw(WRITE_FILE_TEST);
    std::string s("https://774.491.555.829:0:48:8306\nhttps://713D.eklAI:1:78:3:153/ABAV\nhttps://774.491.555.829:0:48:8306\nhttps://774.491.555.829:0:48:8306\n");
    fw.create_file();
    fw.write_str_on_end(s);
    std::unordered_map<std::string,int64_t> agg = fw.get_file_agg();
    std::unordered_map<std::string,int64_t> agg_cmp;
    agg_cmp["https://774.491.555.829:0:48:8306"] += 3;
    agg_cmp["https://713D.eklAI:1:78:3:153/ABAV"] = 1;
    BOOST_CHECK(cmp_agg(agg_cmp,agg));
    std::unordered_map<std::string,int64_t> agg_write;
    agg_write["ftp://x3L7.QFjKX:737:02/E4bZ"] += 1;
    agg_write["https://713D.eklAI:1:78:3:153/ABAV"] +=2;
    fw.write_agg(agg_write);
    std::unordered_map<std::string,int64_t> agg_cmp2 = agg_cmp;
    agg_cmp2["ftp://x3L7.QFjKX:737:02/E4bZ"] += 1;
    agg_cmp2["https://713D.eklAI:1:78:3:153/ABAV"] += 2;
    std::unordered_map<std::string,int64_t> agg2 = fw.get_file_agg();
    BOOST_CHECK(cmp_agg(agg_cmp2,agg2));
    fw.remove_file();
}

BOOST_AUTO_TEST_SUITE_END()






