#pragma once
#include"mat.hpp"
template<class mint,class Graph>
mint CountingSpanningTree(const Graph&g){
    assert(Graph::directed()==false);
    int n=g.size();
    Matrix<mint>mt(n-1,n-1);
    REP(i,1,n){
        mt[i-1][i-1]=g[i].size();
        for(auto&e:g[i]){
            if(e.to)mt[i-1][e.to-1]-=1;
        }
    }
    rep(i,n-1)rep(j,n-1)dbg(mt[i][j]);
    return mt.det();
}