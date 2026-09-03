#pragma once
//N=2 に注意
template<class Graph>
vc<int>stnumbering(Graph&g,int s,int t){
    assert(Graph::directed()==false);
    int n=g.size();
    if(n==2){
        for(auto&e:g[s]){
            if(e.to==t)return vc<int>{s==0?0:1,s==0?1:0}; 
        }
        return {};
    }
    vc<int>par(n,-1);
    vc<int>sign(n);
    vc<int>ord(n);vc<pii>low(n,{-1,-1});
    vc<list<int>::iterator>pos(n);
    list<int>L{s,t};pos[s]=L.begin();pos[t]=next(pos[s]);
    sign[s]=-1;
    vc<int>pers;
    int ng=0;
    int id=1;
    ord[s]=0;low[s]={0,s};
    auto dfs=[&](auto&dfs,int u,int eid)->void{
        ord[u]=id;low[u]={id++,u};
        pers.pb(u);
        for(auto&e:g[u]){
            if(e.id==eid)continue;
            if(low[e.to].fi==-1){
                par[e.to]=u;
                dfs(dfs,e.to,e.id);
                chmin(low[u],low[e.to]);
                ng|=ord[u]<=low[e.to].fi;
            }else{
                chmin(low[u],pii{ord[e.to],e.to});
            }
        }
    };
    dfs(dfs,t,-1);
    
    ng|=pers.size()!=n-1;
    if(ng)return{};
    pers.erase(pers.begin());
    
    for(auto&x:pers){
        if(sign[low[x].se]==-1){
            pos[x]=L.insert(pos[par[x]],x);
            sign[par[x]]=+1;
        }else{
            pos[x]=L.insert(next(pos[par[x]]),x);
            sign[par[x]]=-1;
        }
    }
    
    vc<int>res(n);
    int i=0;for(auto&x:L){
        res[x]=i++;
    }
    return res;
}