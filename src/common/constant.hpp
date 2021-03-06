//
//  constant.hpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/5.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#ifndef constant_hpp
#define constant_hpp

#include <stdio.h>
#include <cstring>
#include <string>
#include <string.h>


const std::string INPUT_FILE = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/urls.txt";
const std::string INPUT_FILE_TEST = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/urls_test.txt";
const std::string INPUT_FILE_TEST_2 = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/urls_test_statistic.txt";
const std::string INPUT_FILE_1G = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/urls_1G.txt";
const std::string INPUT_FILE_1G_P1 = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/urls_1G.txt_1";
const std::string INPUT_FILE_AGG_1 = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/urls_test agg1.txt";
const std::string INPUT_FILE_AGG_2 = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/urls_test agg2.txt";
const std::string OUTPUT_FILE = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/output_topk.txt";
const std::string WRITE_FILE_TEST = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/urls_write_test.txt";
const std::string LOG_FILE = "/Users/wenkchen/Documents/xcodeworkspace/urlquerier/urlquerier/src/test/data/log/run.log";
const int64_t GB = (int64_t)1024*1024*1024;
const int64_t MB = (int64_t)1024*1024;
const int URL_LENGTH_MAX = 256;
const int URL_AVERAGE_BYTES = 30;
const bool LOG_FLAG = true;
const bool STATISTIC_FLAG = true;
const int64_t AGGREGATE_BYTES = (int64_t)300*MB;

#endif /* constant_hpp */
