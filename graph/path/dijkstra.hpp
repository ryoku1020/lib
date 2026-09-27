#pragma once
template<class T,class Graph,class F>
vc<T>dijkstra(const Graph&g,const vc<F>&starts){
    int n=g.size();
    vc<T>md(n,inf<T>);
    smpq<pair<T,int>>que;
    auto push=[&](int x,T d){
        if(chmin(md[x],d))que.push({md[x],x});
    };
    for(auto&x:starts)push(x,0);
    while(que.size()){
        auto[d,v]=que.top();que.pop();
        if(md[v]!=d)continue;
        for(auto&e:g[v]){
            push(e.to,e.cost+d);
        }
    }
    return md;
}
template<class T,class Graph,class F>
vc<T>dijkstra(const Graph&g,int s){
    return dijkstra<T,Graph,int>(g,vc<int>{s});
}