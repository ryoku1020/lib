#pragma once
#include "scc.hpp"
#include "base.hpp"
struct TwoSatisfiability{
    StaticGraph<1>g;
    int n;
    TwoSatisfiability(int n):g(n*2),n(n),ans(n){}
    //a=fa or b=fb という条件を追加
    void add_clause(int a,bool fa,int b,bool fb){
        worked=false;
        assert(0<=a&&a<n&&0<=b&&b<n);
        g.add_edge(a*2+(!fa),b*2+fb);
        g.add_edge(b*2+(!fb),a*2+fa);
    }
    void if_then(int a,bool fa,int b,bool fb){
        worked=false;
        assert(0<=a&&a<n&&0<=b&&b<n);
        g.add_edge(a*2+fa,b*2+fb);
        g.add_edge(b*2+(!fb), a*2+(!fa));
    }
    void set_value(int a,bool fa){
        worked=false;
        assert(0<=a&&a<n);
        g.add_edge(a*2+(!fa),a*2+fa);
    }
    vc<int>ans;
    bool can=false;
    bool worked=false;
    bool satisfiable(){
        if(!worked)work();
        return can;
    }
    vc<int> answer(){
        if(!worked)work();
        return ans;
    }
    void work(){
        worked=true;
        auto res = scc(g);
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
