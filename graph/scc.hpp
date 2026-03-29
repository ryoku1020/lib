#pragma once
#include"../template.hpp"
template<class G>
vc<int>scc(const G& g){
    assert(G::directed()==true);
    int n=g.size();
    vc<int>ord,v1(n),v2(n);
    auto dfs=[&](auto&dfs,int u)->void{
        v1[u]=1;for(auto&e:g[u])if(!v1[e.to])dfs(dfs,e.to);
        ord.pb(u);
    };
    rep(i,n)if(!v1[i])dfs(dfs,i);
    reverse(all(ord));vc<int>res(n);
    int cnt=0;
    auto dfs2=[&](auto&dfs2,int u)->void{
        v2[u]=1;res[u]=cnt;
        for(auto&e:g.inv(u))if(!v2[e.to])dfs2(dfs2,e.to);
    };
    for(int x:ord)if(!v2[x]){dfs2(dfs2,x);++cnt;}
    return res;
}