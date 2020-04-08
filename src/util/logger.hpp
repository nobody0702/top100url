//
//  logger.hpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/6.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#ifndef logger_hpp
#define logger_hpp

#include <stdio.h>
#include <cstring>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include "../common/constant.hpp"


static std::ofstream logfile(LOG_FILE,std::ofstream::binary);


void logger(std::string str);

#endif /* logger_hpp */
