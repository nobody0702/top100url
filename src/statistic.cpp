//
//  statistic.cpp
//  urlquerier
//
//  Created by Chen, Wenkang on 2020/4/5.
//  Copyright © 2020 Chen, Wenkang. All rights reserved.
//

#include "statistic.hpp"
#include "util/logger.hpp"
#include <vector>


statistic::statistic(file* _f, int _top_k):f(_f),top_k(_top_k){
    sample_top_k = top_k*100;
    sample_map.clear();
    while(!topk_pq.empty()){
        topk_pq.pop();
    }
}

void statistic::collect_sample(int sample_number){
    std::unordered_map<std::string, int64_t> sample_agg;
    f->sample_url(sample_number,sample_agg);
    std::vector<std::pair<std::string, int64_t>> sorted(sample_top_k);
    partial_sort_copy(sample_agg.begin(), sample_agg.end(),
                      sorted.begin(), sorted.end(),
                      [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
                          return !(a.second < b.second);
                      });
    // store top k url from sampled data into statistic_map with count initialized with 0
    for(std::pair<std::string, int64_t> p : sorted){
        sample_map[p.first] = -1;
    }
    _sampled = true;
    logger("Finished collect sample, the sample map size is: "+std::to_string(sample_map.size()));
}


void statistic::merge_agg_into_topk(std::unordered_map<std::string, int64_t>& agg){
    std::vector<std::pair<std::string, int64_t>> sorted(top_k);
    partial_sort_copy(agg.begin(), agg.end(),
                      sorted.begin(), sorted.end(),
                      [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b){
                          return !(a.second < b.second);
                      });
    for(std::pair<std::string, int64_t> p : sorted){
        topk_pq.push(make_pair(p.first,p.second));
        if(topk_pq.size() > top_k){
            // pop the smallest cnt element
            topk_pq.pop();
        }
    }
}

void statistic::merge_sample_into_topk(){
    if(sampled() && sample_all_collected()){
        merge_agg_into_topk(sample_map);
    }
}

bool statistic::add_cnt(std::pair<std::string, int64_t> url_pair){
    auto it = sample_map.find(url_pair.first);
    if(it == sample_map.end()){
        return false;
    }
    if(sample_map[url_pair.first] == -1){
        sample_map[url_pair.first] = url_pair.second;
        return true;
    }
    else if(sample_map[url_pair.first] > 0){
        sample_map[url_pair.first] += url_pair.second;
        return true;
    }
    return false;
}

bool statistic::sampled(){
    return !sample_map.empty();
}

bool statistic::sample_all_collected(){
    return _sample_all_collected;
}
void statistic::set_sample_all_collected(){
    if(sampled()){
        _sample_all_collected = true;
    }
}


void statistic::output_topk(file* f){
    std::unordered_map<std::string, int64_t> temp_agg;
    while(!topk_pq.empty()){
        temp_agg.insert(topk_pq.top());
        topk_pq.pop();
    }
    f->create_file();
    f->write_agg(temp_agg);
    for(auto tuple: temp_agg){
        topk_pq.push(tuple);
    }
}
