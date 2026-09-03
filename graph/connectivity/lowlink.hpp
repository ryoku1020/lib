#pragma once
#include"../../tree/base.hpp"
template<class G_>
struct lowlink{
    G_ g;
    int n;
    vc<int>low,ord,parid;
    lowlink(G_ gg):g(gg),n(gg.size()),low(n,inf<int>),ord(n),parid(n,-1){build();}
    void build(){
        assert(G_::directed()==false);
        vc<int>used(n);
        rep(i,n){
            if(!chmax(used[i],1))continue;
            int id=0;
            auto dfs=[&](auto&dfs,int u,int eid)->void{
                ord[u]=low[u]=id++;
                for(auto&e:g[u]){
                    if(e.id==eid)continue;
                    if(!chmax(used[e.to],1)){
                        chmin(low[u],ord[e.to]);
                        continue;
                    }
                    parid[e.to]=e.id;
                    dfs(dfs,e.to,e.id);
                    chmin(low[u],low[e.to]);
                }
            };
            dfs(dfs,i,-1);
        }
    }
    int isbridge(int eid){
        int u=g.get_edge(eid).from;
        int v=g.get_edge(eid).to;
        if(ord[u]>ord[v])swap(u,v);
        return ord[u]<low[v];  
    }
    struct edgecomponent{
        vc<int>toid;
        tree<unweighted>comp;
    };
    edgecomponent twoedge_component(){
        vc<int>used(n);
        vc<int>toid(n);
        int ID=0;
        rep(i,n){
            if(!chmax(used[i],1))continue;
            auto dfs=[&](auto&dfs,int u)->void{
                toid[u]=ID;
                for(auto&e:g[u]){
                    if(!isbridge(e.id)&&chmax(used[e.to],1)){
                        dfs(dfs,e.to);
                    }
                }
            };dfs(dfs,i);
            ID++;
        }
        tree<unweighted>cp(ID);
        rep(i,n)for(auto&e:g[i])if(toid[i]!=toid[e.to]){
            if(toid[i]<toid[e.to])cp.add_edge(toid[i],toid[e.to]);
        }
        return{toid,cp};
    }
    struct vertexcomponent{
        vc<vc<int>>egs;
        tree<unweighted>comp;
    };
    vertexcomponent twovertex_component(){
        vc<vc<int>>egs;
        int m=g.edge_size();
        vc<int>used(n);
        vc<int>st;
        auto dfs=[&](auto&dfs,int u,int vid)->void{
            chmax(used[u],1);
            for(auto&e:g[u]){
                if(e.id==vid)continue;
                if(parid[e.to]==e.id){
                    st.pb(e.id);
                    dfs(dfs,e.to,e.id);
                    if(ord[u]<=low[e.to]){
                        egs.pb({});
                        while(1){
                            int L=st.back();st.pop_back();
                            egs.back().pb(L);
                            if(L==e.id)break;
                        }
                    }
                }else if(ord[u]>ord[e.to]){
                    st.pb(e.id);
                }
            }
        };
        rep(i,n)if(chmax(used[i],1)){
            dfs(dfs,i,-1);
        }
        tree<unweighted>G(n+egs.size());
        vc<int>add(n);
        rep(i,egs.size()){
            for(auto&e:egs[i]){
                if(chmax(add[g.get_edge(e).from],1)){
                    G.add_edge(i+n,g.get_edge(e).from);
                }
                if(chmax(add[g.get_edge(e).to],1)){
                    G.add_edge(i+n,g.get_edge(e).to);
                }
            }
            for(auto&e:egs[i]){
                add[g.get_edge(e).from]=add[g.get_edge(e).to]=0;
            }
        }
        return{egs,G};
    }
};