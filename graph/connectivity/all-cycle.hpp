#pragma once
template<class Graph>
pair<vvc<int>,vvc<int>>all_cycle(Graph&g){
    int n=g.size();
    int m=g.edge_size();
    vc<int>seen(n);
    vc<int>rvs;
    vc<typename Graph::Edge>pare(n,{-1,-1,-1,-1});
    vc<int>x(n);
    vc<int>fem(m,1);
    auto dfs=[&](auto&dfs,int u,int eid)->void{
        for(auto&e:g[u]){
            if(chmax(seen[e.to],1)){
                fem[e.id]=0;
                pare[e.to]=e;
                dfs(dfs,e.to,e.id);
            }else if(e.id!=eid&&u<e.to)x[u]^=1,x[e.to]^=1;
        }
        rvs.pb(u);
    };
    rep(i,n)if(chmax(seen[i],1))dfs(dfs,i,-1);
    for(auto&e:rvs)if(pare[e].id!=-1){
        x[pare[e].from]^=x[e];
        if(x[e]){
            fem[pare[e].id]=1;
        }
    }
    vc<int>used(m);
    seen.assign(n,0);
    vc<int>itr(n);
    auto skip=[&](int S){
        while(itr[S]<g[S].size()){
            if(used[g[S][itr[S]].id]==0&&fem[g[S][itr[S]].id]){
                break;
            }
            itr[S]++;
        }
    };
    vvc<int>vps,eps;
    rep(i,n){
        skip(i);
        if(itr[i]==g[i].size())continue;
        vc<int>vpath{(int)i};
        vc<int>epath;
        int v=i;seen[v]=1;
        while(1){
            skip(v);
            if(itr[v]==g[v].size())break;
            if(seen[g[v][itr[v]].to]){
                int target=g[v][itr[v]].to;
                vc<int>rvpath;
                vc<int>repath{g[v][itr[v]].id};
                while(vpath.back()!=target){
                    rvpath.pb(vpath.back());seen[vpath.back()]=0;vpath.pop_back();
                    repath.pb(epath.back());epath.pop_back();
                }
                rvpath.pb(target);
                reverse(all(rvpath));reverse(all(repath));
                vps.pb(rvpath),eps.pb(repath);
                for(auto&x:repath)used[x]=1;
                v=target;
            }else{
                vpath.pb(g[v][itr[v]].to);
                epath.pb(g[v][itr[v]].id);
                used[g[v][itr[v]].id]=1;
                v=g[v][itr[v]].to;seen[v]=1;
            }
        }
    }
    return{vps,eps};
}