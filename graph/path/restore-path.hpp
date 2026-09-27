#pragma once
template<class graph,class T>
pair<vc<int>,vc<typename graph::edge>>restore_path(const graph&g,const vc<T>&md,int s,int t){
    int n=g.size();
    vc<int>par(n,-1);
    vc<int>pe(n,-1);
    queue<int>q;
    par[s]=s;
    q.push(s);
    while(!q.empty()){
        int u=q.front();q.pop();
        if(u==t)break;
        rep(i,g[u].size()){
            const auto&e=g[u][i];
            int v=e.to;
            if(par[v]!=-1)continue;
            if(md[u]+e.cost!=md[v])continue;
            par[v]=u;
            pe[v]=i;
            q.push(v);
        }
    }
    if(par[t]==-1)return {{},{}};
    vc<int>vs;
    vc<typename graph::edge>es;
    for(int v=t;v!=s;v=par[v]){
        vs.pb(v);
        es.pb(g[par[v]][pe[v]]);
    }
    vs.pb(s);
    reverse(all(vs));
    reverse(all(es));
    return {vs,es};
}