#pragma once
#include"base.cpp"
template<class G>
vvc<int>scc(const G& g){
    int n=g.size();
    vc<int>ord,v1(n),v2(n);
    auto dfs=[&](auto&dfs,int u)->void{
        v1[u]=1;for(auto&e:g[u])if(!v1[e.to])dfs(dfs,e.to);
        ord.pb(u);
    };
    rep(i,n)if(!v1[i])dfs(dfs,i);
    reverse(all(ord));vvc<int>res;
    auto dfs2=[&](auto&dfs2,int u)->void{
        v2[u]=1;res.back().pb(u);
        for(auto&e:g.inv(u))if(!v2[e.to])dfs2(dfs2,e.to);
    };
    for(int x:ord)if(!v2[x]){res.pb({});dfs2(dfs2,x);}
    return res;
}