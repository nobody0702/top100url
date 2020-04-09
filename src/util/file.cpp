//
//  file.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/5.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "file.hpp"
#include "../common/constant.hpp"
#include "../util/logger.hpp"
#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <random>
#include <map>
#include <unordered_map>



file::file(std::string file_path):path(file_path){
}



std::string file::get_path(){
    return path;
}



void file::sample_url(int n, std::unordered_map<std::string, int64_t>& ret){
    auto length = filesize();
    std::default_random_engine generator;
    std::uniform_int_distribution<int64_t> distr(0, (int64_t)length);
    for (int i=0; i<n; ++i) {
        int64_t random_pos = distr(generator);
        std::string sample_url;
        while((sample_url = get_next_line(random_pos))==""){}
        ret[sample_url]++;
    }
}


std::unordered_map<std::string, int64_t> string_to_agg(std::string& block){
    std::unordered_map<std::string, int64_t> agg;
    agg.clear();
    int i = 0;
    while(i < block.size()){
        std::string url = "";
        while(block[i] != ' ' && block[i] != '\n'){
            url.push_back(block[i]);
            i++;
        }
        if(block[i] == ' '){
            int64_t num = 0;
            i++;
            while(block[i] != '\n'){
                num *= 10;
                num += block[i]-'0';
                i++;
           }
           agg[url]+= num;
           i++;
        }
        else{
            agg[url]++;
            i++;
        }
    }
    std::string().swap(block);
    return agg;
}


std::unordered_map<std::string,int64_t> file::get_file_agg(){
    std::string input = get_string(0, int(filesize()));
    return string_to_agg(input);
}

std::string file::get_string(int64_t pos, int length){
    std::ifstream is (path, std::ifstream::binary);
    std::string ret = "";
    int64_t i;
    try{
        is.seekg(pos, is.beg);
        char * buffer = new char[length+1];
        buffer[0] = 0;
        is.read(buffer,length);
        buffer[length] = 0;
        i = 0;
        while(buffer[i] != 0){
            ret.push_back(buffer[i]);
            i++;
        }
        delete[] buffer;
        buffer = NULL;
    }catch(std::exception& e){
        logger("exception: " + std::string(e.what()));
    }
    return ret;
}

std::string file::get_this_line(int64_t pos){
    std::ifstream is (path, std::ifstream::binary);
    std::string ret = "";
    int64_t i;
    try{
        is.seekg(pos, is.beg);
        char * buffer = new char[URL_LENGTH_MAX+1];
        buffer[0] = 0;
        is.getline(buffer,URL_LENGTH_MAX);
        buffer[URL_LENGTH_MAX] = 0;
        i = 0;
        while(buffer[i] != 0){
            ret.push_back(buffer[i]);
            i++;
        }
    }catch(std::exception& e){
        logger("exception: " + std::string(e.what()));
    }
    return ret;
}

int64_t file::get_next_line_pos(int64_t pos){
    std::ifstream is (path, std::ifstream::binary);
    std::string ret = "";
    if(pos == 0) return 0;
    int64_t i;
    try{
        is.seekg(pos, is.beg);
        char * buffer = new char[URL_LENGTH_MAX+1];
        buffer[0] = 0;
        is.read(buffer,URL_LENGTH_MAX);
        buffer[URL_LENGTH_MAX] = 0;
        
        i=pos;
        while(buffer[i-pos] != '\n' && buffer[i-pos] !=0){
            i++;
        }
        delete[] buffer;
        buffer = NULL;
    }catch(std::exception& e){
        logger("exception: " + std::string(e.what()));
    }
    return i+1;
}

std::string file::get_next_line(int64_t pos){
    std::ifstream is (path, std::ifstream::binary);
    std::string ret = "";
    int64_t i;
    if(is){
        try{
            char * buffer = new char[URL_LENGTH_MAX+1];
            buffer[0] = 0;
            is.seekg(get_next_line_pos(pos), is.beg);
            is.getline(buffer,URL_LENGTH_MAX);
            buffer[URL_LENGTH_MAX] = 0;
            i = 0;
            while(buffer[i] != '\n' && buffer[i] !=0){
                ret.push_back(buffer[i]);
                i++;
            }
            delete[] buffer;
            buffer = NULL;
        }catch(std::exception& e){
            logger("exception: " + std::string(e.what()));
        }
    }
    is.close();
    return ret;
}


int64_t file::write_str_on_end(std::string& str){
    std::ofstream of(path,std::ios::binary|std::ios::out|std::ios::in);
    int64_t length = filesize();
    of.seekp((int64_t)length);
    of.write(str.c_str(),str.size());
    of.close();
    return (int64_t)length+str.size();
}


void file::create_file(){
    std::ofstream of(path,std::ios::binary|std::ios::out|std::ios::in);
    if(!of.is_open()){
        of.open(path);
    }
}


void file::remove_file(){
    remove(path.c_str());
}

bool file::is_empty(){
    std::ofstream of(path,std::ios::binary|std::ios::out|std::ios::in);
    if(!of.is_open()){
        return true;
    }
    return (int64_t)filesize() == 0;
}

void file::replace_byte(int64_t pos,char* ch){
    std::ofstream of(path,std::ios::binary|std::ios::out|std::ios::in);
    of.seekp((int64_t)pos);
    of.write(ch,1);
    of.close();
}


std::ifstream::pos_type file::filesize()
{
    std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
    return in.tellg();
}

void file::mv_replace(std::string tmp_file_name){
    try{
        remove_file();
        rename(tmp_file_name.c_str(),path.c_str());
    }catch(std::exception& e){
        logger("exception: " + std::string(e.what()));
    }
}

std::unordered_map<std::string,int64_t> file::get_agg(int64_t pos, int length){
    std::string block = get_string(pos,length);
    return string_to_agg(block);
}

void file::write_agg(std::unordered_map<std::string,int64_t> agg){
    std::string output = "";
    for(auto tuple: agg){
        output += tuple.first + " " + std::to_string(tuple.second) + "\n";
    }
    write_str_on_end(output);
}
