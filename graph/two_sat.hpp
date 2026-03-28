#pragma once
#include "scc.hpp"
struct TwoSatisfiability{
    StronglyConnectedComponents sc;
    int n;
    TwoSatisfiability(int n):n(n),sc(n*2),ans(n){}
    //a=fa or b=fb という条件を追加
    void add_clause(int a,bool fa,int b,bool fb){
        assert(0<=a&&a<n&&0<=b&&b<n);
        sc.add_edge(a*2+(!fa),b*2+fb);
        sc.add_edge(b*2+(!fb),a*2+fa);
    }
    void if_then(int a,bool fa,int b,bool fb){
        assert(0<=a&&a<n&&0<=b&&b<n);
        sc.add_edge(a*2+fa,b*2+fb);
        sc.add_edge(b*2+(!fb), a*2+(!fa));
    }
    void set_value(int a,bool fa){
        assert(0<=a&&a<n);
        sc.add_edge(a*2+(!fa),a*2+fa);
    }
    vc<int>ans;
    bool can=false;
    bool satisfiable(){
        work();
        return can;
    }
    vc<int> answer(){
        return ans;
    }
    void work(){
        vvc<int> scc_res = sc.do_scc();
        vc<int> comp(n*2);
        rep(i, scc_res.size()) {
            for (int u : scc_res[i]) comp[u] = i;
        }
        auto res = comp;
        vc<int>Id(n*2);
        rep(i,n*2)Id[i]=res[i];
        rep(i,n)if(Id[i*2]==Id[i*2+1]){
            can=0;
            return;
        }
        can=1;
        rep(i,n){
            if(Id[i*2]<Id[i*2+1])ans[i]=1;
            else ans[i]=0;
        }
    }
};