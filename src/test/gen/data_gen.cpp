//
//  data_gen.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/4.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "../../common/constant.hpp"
#include "../../util/file.hpp"
#include <cstring>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>



const int batch_count = 1024;
std::string header[3] = {"http","ftp","https"};
char atozAtoZ0to9dotlinedash_pattern_charsets[65] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9','.','_','-'};
char atozAtoZ_pattern_charsets[52] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
char onetonine_pattern_charsets[10] = {'0','1','2','3','4','5','6','7','8','9'};
char atozAtoZ0to9andmorechar_pattern_charsets[69] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','0','1','2','3','4','5','6','7','8','9','.','_','-','&','~','/','%'};



//generate from regex:
//((http|ftp|https)://)(([a-zA-Z0-9\._-]+\.[a-zA-Z]{2,6})|([0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}))(:[0-9]{1,4})*(/[a-zA-Z0-9\&%_\./-~-]*)?
std::string generate_url(){
    std::string url = "";
    url += header[rand()%3]+"://";
    if(rand()%2 == 1){
       int len = rand()%5+1;
       for(int i=0;i<len;i++){
            url.push_back(atozAtoZ0to9dotlinedash_pattern_charsets[rand()%65]);
       }
       url.push_back('.');
       for(int i=2;i<=6;i++){
           url.push_back(atozAtoZ_pattern_charsets[rand()%52]);
       }
    }
    else{
        bool first = true;
        for(int i=0;i<4;i++){
            if(first){
                first = false;
            }
            else{
                url.push_back('.');
            }
            for(int j=0;j<3;j++){
                url.push_back(onetonine_pattern_charsets[rand()%10]);
            }
        }
    }
    int len = rand()%5;
    for(int i=0;i<len;i++){
        url.push_back(':');
        int len2 = rand()%4+1;
        for(int j=0;j<len2;j++){
            url.push_back(onetonine_pattern_charsets[rand()%10]);
        }
    }
    if(rand()%2 == 1){
        url.push_back('/');
        int len3 = rand()%5;
        for(int i=0;i<len3;i++){
            url.push_back(atozAtoZ0to9andmorechar_pattern_charsets[rand()%69]);
        }
    }
    return url;
}


//generate 100G url data
void gen_data(int data_size, char* path) {
    
    std::ofstream outfile(path);
    
    
    file f(path);
    //while file size less than 100G+1M
    while(f.filesize() < (int64_t)data_size*GB+MB){
        for (int count = 0; count < batch_count; count++) {
            //clock_t start = clock();
            outfile << generate_url()+"\n";
            //std::cout << (clock() - start) * 1.0 / CLOCKS_PER_SEC * 1000 << std::endl;
        }
    }
    
    outfile.close();
}


