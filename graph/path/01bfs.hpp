#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class T,class Graph,class F>
vc<T>bfs01(const Graph&g,const vc<F>&starts){
    int n=g.size();
    vc<T>md(n,inf<T>);
    deque<pair<T,int>>que;
    auto push=[&](int x,T d,bool back){
        if(chmin(md[x],d)){
            if(back)que.push_back({md[x],x});
            else que.push_front({md[x],x});
        }
    };
    for(auto&x:starts)push(x,0,0);
    while(que.size()){
        auto[d,v]=que.front();que.pop_front();
        if(md[v]!=d)continue;
        for(auto&e:g[v]){
            assert(e.cost==0||e.cost==1);
            push(e.to,d+e.cost,e.cost==1);
        }
    }
    return md;
}
template<class T,class Graph>
vc<T>bfs01(const Graph&g,int s){
    return bfs01<T,Graph,int>(g,vc<int>{s});
}

}
