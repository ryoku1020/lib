#pragma once
#include <cassert>
#include <random>
#include <vector>

#include "random-tree.hpp"

inline std::vector<int> randomsequence(int n,int m){
    assert(n>=0);
    assert(n==0||m>0);
    std::vector<int> res(n);
    if(n==0)return res;
    std::uniform_int_distribution<int> dist(0,m-1);
    for(auto&x:res)x=dist(generator_engine());
    return res;
}
