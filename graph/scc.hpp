#pragma once
#include "CSR.hpp"
struct StronglyConnectedComponents{
    int n;
    CSRgraph g,inv;
    StronglyConnectedComponents(int n):n(n),g(n),inv(n){}
    void add(int a,int b){
        assert(0<=a&&a<n&&0<=b&&b<n);
        g.add_edge(a,b);
        inv.add_edge(b,a);
    }
    vvc<int>do_scc(){
        g.build(),inv.build();
        vc<int>seen(n),seen2(n);
        vc<int>ord;
        rep(i,n){
            if(chmax(seen[i],1)){
                auto dfs=[&](auto&dfs,int u)->void{
                    for(auto&x:g[u]){
                        if(chmax(seen[x],1))dfs(dfs,x);
                    }
                    ord.push_back(u);
                };
                dfs(dfs,i);
            }
        }
        vvc<int>res;
        drep(i,n){
            int x=ord[i];
            if(chmax(seen2[x],1)){
                res.push_back({});
                auto dfs=[&](auto&dfs,int u)->void{
                    res.back().push_back(u);
                    for(auto&x:inv[u])if(chmax(seen2[x],1))dfs(dfs,x);
                };
                dfs(dfs,x);
            }
        }
        return res;
    }
};
