#pragma once
#include"base.hpp"
struct bipartite_matching{
    using graph=static_graph<0>;
    int l,r;
    vc<int>pm,qm;
    vvc<int>g;
    vc<graph::edge>es;
    vc<int>pe;
    vc<int>dist;
    bipartite_matching(int l,int r):l(l),r(r){
        assert(l>=0&&r>=0);
        pm.assign(l,-1);
        qm.assign(r,-1);
        g.resize(l);
        pe.assign(l,-1);
        dist.resize(l);
    }
    void add_edge(int a,int b,int id=-1){
        assert(0<=a&&a<l);
        assert(0<=b&&b<r);
        if(id==-1)id=es.size();
        es.pb({a,b,id});
        g[a].push_back(es.size()-1);
    }
    bool bfs(){
        queue<int>que;
        bool find=0;
        fill(all(dist),-1);
        rep(i,l){
            if(pm[i]==-1){
                dist[i]=0;
                que.push(i);
            }
        }
        while(que.size()){
            auto u=que.front();que.pop();
            for(auto&x:g[u]){
                int nu=qm[es[x].to];
                if(nu==-1){
                    find=1;
                }else if(dist[nu]==-1){
                    dist[nu]=dist[u]+1;
                    que.push(nu);
                }
            }
        }
        return find;
    }
    bool dfs(int u){
        assert(0<=u&&u<l);
        for(auto&x:g[u]){
            int nu=qm[es[x].to];
            if(nu==-1||(dist[nu]==dist[u]+1&&dfs(nu))){
                qm[es[x].to]=u;
                pm[u]=es[x].to;
                pe[u]=x;
                return 1;
            }
        }
        dist[u]=-1;
        return 0;
    }
    vc<graph::edge> work(){
        while(bfs()){
            rep(i,l)if(pm[i]==-1)dfs(i);
        }
        vc<graph::edge>ans;
        rep(i,l)if(pm[i]!=-1)ans.pb(es[pe[i]]);
        return ans;
    }
};
