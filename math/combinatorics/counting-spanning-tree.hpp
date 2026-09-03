#pragma once
#include"../mat.hpp"
template<class mint,class Graph>
mint counting_spanning_tree(const Graph&g){
    assert(Graph::directed()==false);
    int n=g.size();
    matrix<mint>mt(n-1,n-1);
    REP(i,1,n){
        mt[i-1][i-1]=g[i].size();
        for(auto&e:g[i]){
            if(e.to)mt[i-1][e.to-1]-=1;
        }
    }
    return mt.det();
}
