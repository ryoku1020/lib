#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class Graph>
vc<int>biparate_coloring(const Graph&g){
    int n=g.size();
    vc<int>col(n,-1);
    rep(i,n){
        if(col[i]!=-1)continue;
        col[i]=0;
        auto dfs=[&](auto&dfs,int u)->bool{
            for(auto&e:g[u]){
                if(col[e.to]!=-1){
                    if(col[e.to]==col[u])return 0;
                }
                else{
                    col[e.to]=col[u]^1;
                    if(!dfs(dfs,e.to))return 0;
                }
            }
            return 1;
        };
        if(!dfs(dfs,i))return{};
    }
    return col;
}
}
