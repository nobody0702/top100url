//
//  statistic.hpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/5.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#ifndef statistic_hpp
#define statistic_hpp
#include "util/file.hpp"
#include <stdio.h>
#include <string.h>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <queue>


class comparedist
{
public:
    bool operator()(std::pair<std::string,int64_t> n1,std::pair<std::string,int64_t> n2) {
        return n1.second>n2.second;
    }
};

class statistic{
public:
    statistic(file* _f, int top_k);
    void collect_sample(int sample_number);
    bool add_cnt(std::pair<std::string, int64_t> url_pair);
    bool sampled();
    bool sample_all_collected();
    void set_sample_all_collected();
    void merge_sample_into_topk();
    void merge_agg_into_topk(std::unordered_map<std::string, int64_t>& agg);
    void output_topk(file* f);
private:
    std::unordered_map<std::string,int64_t> sample_map;
    std::priority_queue<std::pair<std::string,int64_t>,
                       std::vector<std::pair<std::string, int64_t>>,
                       comparedist> topk_pq;
    file* f;
    int top_k;
    int sample_top_k;
    bool _sampled = false;
    bool _sample_all_collected = false;
};

#endif /* statistic_hpp */

