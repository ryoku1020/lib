#pragma once
#include"base.hpp"
template<class T>
struct virtualtree{
    tree<T>g;
    int n;
    vvc<int>resg;
    vc<int>active;
    struct view{
        const vvc<int>*g;
        const vc<int>&operator[](int v)const{
            return (*g)[v];
        }
    };
    virtualtree(tree<T>g):g(g),n(g.size()){
        resg.resize(n);
        g.build();
    }
    view call(vc<int>vs,int both){
        clearg();
        if(vs.size()==0){
            return view{&resg};
        }
        if(g.built_hld==-1){
            g.build();
        }
        sort(all(vs),[&](auto a,auto b){
            return g.in[a]<g.in[b];
        });
        int V=vs.size();
        rep(i,V-1){
            vs.pb(g.lca(vs[i],vs[i+1]));
        }
        vs.pb(0);
        sort(all(vs),[&](auto a,auto b){
            return g.in[a]<g.in[b];
        });
        vs.erase(unique(all(vs)),vs.end());
        vc<pii>res;
        vc<int>st{vs[0]};
        REP(i,1,vs.size()){
            while(st.size()){
                auto p=st.back();
                if(!(g.in[p]<=g.in[vs[i]]&&
                    g.out[vs[i]]<=g.out[p])){
                        st.pop_back();
                    }else break;
            }
            resg[st.back()].pb(vs[i]);
            if(both)resg[vs[i]].pb(st.back());
            st.pb(vs[i]);
        }
        active=std::move(vs);
        return view{&resg};
    }
    void clearg(){
        for(auto&x:active)resg[x].clear();
        active.clear();
    }
};