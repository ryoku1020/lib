#pragma once
#include"../template.hpp"
#include"../graph/base.hpp"
#include"base.hpp"
namespace ryoku{
template<class T>
struct namori{
    static_graph<0,T>g;
    vc<int>group,comp,incycle,inner_id;
    vc<int>cyc;
    vc<T>cycw;
    vc<tree<T>>t;
    vvc<int>vs,comps;
    vc<T>edgew;
    namori(int n):g(n),group(n),comp(n,-1),incycle(n),inner_id(n){
    }
    void add_edge(int a,int b,T c=T()){
        g.add_edge(a,b,c);
        edgew.pb(c);
    }
    void build(){
        int cid=0;
        rep(s,group.size())if(comp[s]==-1){
            comps.pb({});
            auto dfs=[&](auto&dfs,int v)->void{
                comp[v]=cid;
                comps.back().pb(v);
                for(auto&e:g[v]){
                    if(comp[e.to]!=-1)continue;
                    dfs(dfs,e.to);
                }
            };
            dfs(dfs,s);
            cid++;
        }
        auto res=all_cycle(g);
        for(auto&x:res.fi)cyc.pb(x);
        cycw.resize(cyc.size());
        rep(i,cyc.size())cycw[i]=edgew[res.se[i]];
        edgew.clear();
        rep(i,cyc.size())incycle[cyc[i]]=1;
        vs.resize(cyc.size());
        rep(i,cyc.size()){
            int par=cyc[i];
            vc<tuple<int,int,T>>es;
            auto dfs=[&](auto&dfs,int u,int v)->void{
                inner_id[u]=vs[i].size();
                vs[i].pb(u);
                group[u]=i;
                for(auto&e:g[u]){
                    if(e.to==v)continue;
                    if(incycle[e.to])continue;
                    dfs(dfs,e.to,u);
                    es.pb({inner_id[u],inner_id[e.to],e.cost});
                }
            };
            dfs(dfs,par,-1);
            t.pb(tree<T>(vs[i].size()));
            for(auto&[a,b,co]:es)t.back().add_edge(a,b,co);
        }
    }
    int cycle_size()const{
        return cyc.size();
    }
    bool is_cycle(int v)const{
        return incycle[v];
    }
    int cycle_pos(int v)const{
        assert(incycle[v]);
        return group[v];
    }
    int cycle_vertex(int i)const{
        return cyc[i];
    }
    T cycle_edge(int i)const{
        return cycw[i];
    }
    int cycle_next(int i)const{
        return (i+1)%cycle_size();
    }
    int cycle_prev(int i)const{
        return (i+cycle_size()-1)%cycle_size();
    }
    int tree_id(int v)const{
        return group[v];
    }
    int local_id(int v)const{
        return inner_id[v];
    }
    int root(int v)const{
        return cyc[group[v]];
    }
    bool same_tree(int a,int b)const{
        return group[a]==group[b];
    }
    bool same_component(int a,int b)const{
        return comp[a]==comp[b];
    }
    int component_id(int v)const{
        return comp[v];
    }
    int original_id(int k,int v)const{
        return vs[k][v];
    }
    const tree<T>&get_tree(int v)const{
        return t[group[v]];
    }
    const vc<int>&tree_vertices(int v)const{
        return vs[group[v]];
    }
    const vvc<int>&components()const{
        return comps;
    }
    const vvc<int>&tree_components()const{
        return vs;
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
}