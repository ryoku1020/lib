#pragma once
#include <algorithm>
#include <cassert>
#include <random>
#include <utility>
#include <vector>

inline std::mt19937_64& generator_engine(){
    static std::mt19937_64 engine(std::random_device{}());
    return engine;
}

inline std::vector<std::pair<int,int>> randomtree(int n){
    assert(n>=0);
    std::vector<std::pair<int,int>> res;
    res.reserve(std::max(0,n-1));
    for(int i=1;i<n;i++){
        std::uniform_int_distribution<int> dist(0,i-1);
        res.push_back({i,dist(generator_engine())});
    }
    std::shuffle(res.begin(),res.end(),generator_engine());
    return res;
}
