#pragma once
#include "connectivity/scc.hpp"
#include "base.hpp"
struct two_satisfiability{
    static_graph<1>g;
    int n;
    two_satisfiability(int n):g(n*2),n(n),ans(n){}
    //a=fa or b=fb という条件を追加
    void add_clause(int a,bool fa,int b,bool fb){
        worked=false;
        assert(0<=a&&a<n&&0<=b&&b<n);
        g.add_edge(a*2+(!fa),b*2+fb);
        g.add_edge(b*2+(!fb),a*2+fa);
    }
    void lessthan(vc<int>v,vc<int>op){
        assert(v.size()==op.size());
        if(v.size()<=1)return;
        vc<int>s(v.size()-1);
        rep(i,v.size()-1)s[i]=n++;
        g.resize(n*2);
        ans.resize(n);
        if_then(v[0],op[0],s[0],true);
        REP(i,1,v.size()-1){
            if_then(v[i],op[i],s[i],true);
            if_then(s[i-1],true,s[i],true);
            if_then(v[i],op[i],s[i-1],false);
        }
        if_then(v.back(),op.back(),s.back(),false);
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
    int get_new(){
        int res=n++;
        g.resize(n*2);
        ans.resize(n);
        return res;
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
        vc<int>id(n*2);
        rep(i,n*2)id[i]=res[i];
        rep(i,n)if(id[i*2]==id[i*2+1]){
            can=0;
            return;
        }
        can=1;
        rep(i,n){
            if(id[i*2]<id[i*2+1])ans[i]=1;
            else ans[i]=0;
        }
    }
};
