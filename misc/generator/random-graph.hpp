#pragma once
#include <algorithm>
#include <cassert>
#include <numeric>
#include <random>
#include <unordered_set>
#include <utility>
#include <vector>

#include "random-tree.hpp"

inline std::vector<std::pair<int,int>> randomgraph(int n,int m,bool connected=false){
    assert(n>=0);
    long long max_edges=1LL*n*(n-1)/2;
    assert(0<=m&&m<=max_edges);
    assert(!connected||n==0||m>=n-1);
    std::vector<std::pair<int,int>> res;
    res.reserve(m);
    std::unordered_set<long long> used;
    auto add_edge=[&](int u,int v){
        if(u>v)std::swap(u,v);
        long long id=1LL*u*n+v;
        if(used.insert(id).second)res.push_back({u,v});
    };
    if(connected){
        auto tree=randomtree(n);
        for(auto [u,v]:tree)add_edge(u,v);
    }
    if(max_edges<=2LL*m){
        std::vector<std::pair<int,int>> edges;
        edges.reserve(max_edges-res.size());
        for(int u=0;u<n;u++)for(int v=u+1;v<n;v++){
            long long id=1LL*u*n+v;
            if(!used.count(id))edges.push_back({u,v});
        }
        std::shuffle(edges.begin(),edges.end(),generator_engine());
        while((int)res.size()<m){
            auto [u,v]=edges.back();
            edges.pop_back();
            add_edge(u,v);
        }
    }else{
        std::uniform_int_distribution<int> dist(0,n-1);
        while((int)res.size()<m){
            int u=dist(generator_engine());
            int v=dist(generator_engine());
            if(u==v)continue;
            add_edge(u,v);
        }
    }
    std::shuffle(res.begin(),res.end(),generator_engine());
    return res;
}
