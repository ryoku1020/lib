#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class T,class Graph,class F>
vc<T>bfs(const Graph&g,const vc<F>&starts){
    int n=g.size();
    vc<T>md(n,inf<T>);
    queue<int>que;
    auto push=[&](int x,T d){
        if(chmin(md[x],d))que.push(x);
    };
    for(auto&x:starts)push(x,0);
    while(que.size()){
        int v=que.front();que.pop();
        for(auto&e:g[v]){
            push(e.to,md[v]+e.cost);
        }
    }
    return md;
}
template<class T,class Graph>
vc<T>bfs(const Graph&g,int s){
    return bfs<T,Graph,int>(g,vc<int>{s});
}

}
