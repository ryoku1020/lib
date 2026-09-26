#pragma once
template<class T,class Graph,class F>
vc<T>slow_dijkstra(const Graph&g,vc<F>starts){
    int n=g.size();
    vc<T>md(n,inf<T>);
    for(auto&x:starts)md[x]=0;
    vc<int>done(n);
    rep(i,n){
        pair<T,int>target{inf<T>,-1};
        rep(j,n){
            if(!done[j]){
                chmin(target,pair<T,int>{md[j],j});
            }
        }
        if(target.se==-1)continue;
        done[target.se]=1;
        for(auto&e:g[target.se]){
            chmin(md[e.to],md[target.se]+e.cost);
        }
    }
    return md;
}