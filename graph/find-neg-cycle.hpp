#pragma once
template<class T,class G>
vc<int>findnegcycle(G g){
    int n=g.size();
    vc<int>par(n,-1);
    vc<T>md(n);
    int x=-1;
    rep(t,n){
        x=-1;
        rep(i,n)for(auto&e:g[i]){
            if(chmin(md[e.to],md[i]+e.cost)){
                x=e.to;
                par[x]=i;
            }
        }
    }
    if(x==-1)return{};
    rep(i,n)x=par[x];
    vc<int>cycle;
    int v=x;
    while(1){
        cycle.pb(v);
        v=par[v];
        if(v==x)break;
    }   
    reverse(all(cycle));
    return cycle;
}