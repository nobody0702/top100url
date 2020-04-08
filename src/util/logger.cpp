//
//  logger.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/6.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "logger.hpp"
#include <mutex>


std::mutex logmtx;
// a simple logger to print string on both screen and log file.
void logger(std::string str){
    if(LOG_FLAG == false) return;
    logmtx.lock();
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::string time_str = std::ctime(&now_time);
    std::string log_context = time_str.substr(0,time_str.size()-1) +" : "+str +"\n";
    std::cout << log_context;
    logfile.write(log_context.c_str(),log_context.size());
    logmtx.unlock();
}
