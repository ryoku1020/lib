#pragma once
#include"base.hpp"
template<class G>
struct GraphComponents{
    const G&g;
    GraphComponents(const G&g):g(g){
        assert(G::directed()==false);
    }
    vc<int>edgec2()const{
        int n=g.size();
        vc<int>res(n,-1);
        int id=0;
        rep(i,n){
            auto dfs=[&](auto&dfs,int u)->void{
                for(auto&e:g[u]){
                    if(g.is_bridge(e))continue;
                    if(res[e.to]==-1){
                        res[e.to]=id;
                        dfs(dfs,e.to);
                    }
                }
            };
            if(res[i]==-1){
                res[i]=id;
                dfs(dfs,i);
                ++id;
            }
        }
        return res;
    }
    //辺属性の二重頂点連結成分 孤立点に注意
    vc<int>vertexc2()const{
        int m=g.edge_size();
        int n=g.size();
        vc<int>res(m,-1);
        vc<int>done(m);
        vc<int>seen(n);
        int id=0;
        rep(i,n){
            dbg(i);
            vc<int>stack;
            auto dfs=[&](auto&dfs,int u,int eid)->void{
                for(auto&e:g[u]){
                    if(chmax(done[e.id],1))stack.pb(e.id);
                    if(!seen[e.to]){
                        seen[e.to]=1;
                        dfs(dfs,e.to,e.id);
                        if(g.low(e.to)>=g.ord(u)){
                            while(stack.size()&&stack.back()!=e.id){
                                res[stack.back()]=id;stack.pop_back();
                            }
                            res[stack.back()]=id;stack.pop_back();
                            ++id;
                        }
                    }
                }
            };
            if(chmax(seen[i],1))dfs(dfs,i,-1);
        }
        return res;
    }
    //頂点属性の二重頂点連結成分
    vvc<int>vertexc2vertex()const{
        int n=g.size();
        int m=g.edge_size();
        vvc<int>res;
        auto id=vertexc2();
        if(id.empty()){
            vvc<int>res(n);
            rep(i,n)res[i]={(int)i};
            return res;
        }
        vvc<int>es(max(id)+1);rep(i,m)es[id[i]].pb(i);
        vc<int>seen(n);
        for(auto&x:es){
            vc<int>vs;
            for(auto&e:x){
                int u=g.get_edge(e).from;
                int v=g.get_edge(e).to;
                if(chmax(seen[u],1))vs.pb(u);
                if(chmax(seen[v],1))vs.pb(v);
            }   
            res.pb(vs);
            for(auto&x:vs)seen[x]=0;
        }
        rep(i,n)if(g.deg(i)==0)res.pb(vc<int>{(int)i});
        return res;
    }
};
