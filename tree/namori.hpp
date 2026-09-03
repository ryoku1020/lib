#pragma once
#include"../graph/base.hpp"
#include"base.hpp"
template<class T>
struct namori{
    static_graph<0,T>g;
    vc<int>group,incycle,parinv;
    vc<int>inner_id;
    vc<int>cyc;
    vc<T>cycw;
    vc<tree<T>>t;
    namori(int n):g(n),group(n),incycle(n),parinv(n),inner_id(n){
        
    }
    vc<T>edgew;
    void add_edge(int a,int b,T c=T()){
        g.add_edge(a,b,c);
        edgew.pb(c);
    }
    void build(){
        auto res=cycle_detection(g);
        cyc=std::move(res.fi);
        cycw.resize(cyc.size());
        rep(i,cyc.size())cycw[i]=edgew[res.se[i]];
        edgew.clear();

        rep(i,cyc.size()){
            parinv[cyc[i]]=i;
            incycle[cyc[i]]=1;
        }
        rep(i,cyc.size()){
            int par=cyc[i];
            int id=0;
            vc<tuple<int,int,T>>es;
            auto dfs=[&](auto&dfs,int u,int v)->void{
                inner_id[u]=id++;
                group[u]=i;
                for(auto&e:g[u]){
                    if(e.to==v)continue;
                    if(incycle[e.to])continue;
                    dfs(dfs,e.to,u);
                    es.pb({inner_id[u],inner_id[e.to],e.cost});
                }
            };
            dfs(dfs,par,-1);
            t.pb(tree<T>(id));
            for(auto&[a,b,co]:es){
                t.back().add_edge(a,b,co);
            }
        }
    }
    vc<array<int,3>>path_decomposition(int a,int b){
        if(group[a]==group[b]){
            return{{a,b,0}};
        }
        vc<array<int,3>>res;
        res.pb({a,cyc[group[a]],0});
        res.pb({cyc[group[a]],cyc[group[b]],1});
        res.pb({cyc[group[b]],b,0});
        return res;
    }
};