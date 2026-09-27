#pragma once
#include"../../tree/base.hpp"
#include"Mo.hpp"
struct motree_edge{
    tree<unweighted>g;
    int q;
    motree_edge(int q,const tree<unweighted>&g):q(q),g(g){}
    vc<pii>query;
    void add(int s,int t){query.pb({s,t});}
    void run(auto add,auto erase,auto answer){
        mo mo(g.size()*2,q);
        vc<int>ord;
        vc<int>in(g.size()),out(g.size());
        vc<int>ep(g.size(),-1);
        int id=0;
        auto dfs=[&](auto&dfs,int u,int v)->void{
            ord.pb(u);
            in[u]=id++;
            for(auto&e:g[u]){
                if(e.to==v)continue;
                ep[e.to]=e.id;
                dfs(dfs,e.to,u);
            }
            out[u]=id++;
            ord.pb(u);
        };dfs(dfs,0,-1);
        vc<int>parity(g.size());
        auto togglev=[&](int x){
            parity[x]^=1;
            if(x==0)return;
            if(parity[x]){
                add(ep[x]);
            }else{
                erase(ep[x]);
            }
        };
        auto toggle=[&](int x){
            togglev(ord[x]);
        };
        g.build();
        vc<int>LCA(q);
        vc<int>need(q);
        rep(i,q){
            int u=query[i].fi,v=query[i].se;
            if(in[u]>in[v])swap(u,v);
            int L=g.lca(u,v);
            LCA[i]=L;
            if(u==L){
                mo.push(in[u]+1,in[v]);
            }else{
                need[i]=1;
                mo.push(out[u],in[v]);
            }
        }
        auto an=[&](int i){
            answer(i);
        };
        mo.run(toggle,toggle,toggle,toggle,an);
    }
};