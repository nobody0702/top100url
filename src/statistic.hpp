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
#include <string>
#include <cstring>
#include <queue>


struct cnt_greater {
    template<typename T, typename U>
    bool operator()(T const& lhs, U const& rhs) const {
        return lhs.second > lhs.second;
    }
};

class statistic{
public:
    statistic(file* _f, int top_k);
    void collect_sample(int sample_number);
    void add_cnt(std::pair<std::string, int64_t> url_pair);
    bool sampled();
    bool sample_all_collected();
    void set_sample_all_collected();
    void merge_sample_into_topk();
    void merge_agg_into_topk(std::map<std::string, int64_t>& agg);
    void output_topk(file* f);
private:
    std::map<std::string,int64_t> sample_map;
    std::priority_queue<std::pair<std::string,int64_t>,
                       std::vector<std::pair<std::string, int64_t>>,
                       cnt_greater> topk_pq;
    file* f;
    int top_k;
    int sample_top_k;
    bool _sampled = false;
    bool _sample_all_collected = false;
};

#endif /* statistic_hpp */

