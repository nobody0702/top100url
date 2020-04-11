//
//  file.hpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/5.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#ifndef file_hpp
#define file_hpp

#include <stdio.h>
#include <string.h>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>

class file{
public:
    file(std::string file_path);
    void sample_url(int n, std::unordered_map<std::string, int64_t>& ret);
    std::ifstream::pos_type filesize();
    //get string from file on position pos with length bytes
    std::string get_string(int64_t pos, int length);
    std::string get_this_line(int64_t pos);
    int64_t get_next_line_pos(int64_t pos);
    //get next url from a file postion, if end of file, return "";
    std::string get_next_line(int64_t pos);
    // write a string on the end of file
    int64_t write_str_on_end(std::string& str);
    // rm file
    void remove_file();
    std::string get_path();
    void create_file();
    bool is_empty();
    //remove current file and move another temp file and replace this file.
    void mv_replace(std::string tmp_file_name);
    //write a file and return a string
    std::string get_file_to_string();
    //get agg from file from adress pos with length
    std::unordered_map<std::string,int64_t> get_agg(int64_t pos, int length);
    //write agg to file
    void write_agg(std::unordered_map<std::string,int64_t> agg);
    //get the file into agg
    std::unordered_map<std::string,int64_t> get_file_agg();
private:
    std::string path;
};

#endif /* file_hpp */

