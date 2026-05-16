#pragma once
#include"../math/fps.hpp"

//s[0,|t|) s[1,|t|+1) ... で match するもの
template<int TF>
vc<int>WildMatch(string s,string t,char wild){
    assert(s.size()>=t.size());
    vc<int>res(s.size()-t.size()+1,1);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    rep(t_,TF){
        map<int,int>ma;
        auto get=[&](int a){
            if(a==wild)return 0;
            if(ma.count(a))return ma[a];
            return ma[a]=rng();
        };
        poly fs1(s.size()),fs2(s.size()),fs3(s.size());
        rep(i,s.size()){
            mint S=get(s[i]);
            fs1[i]=S*S*S;
            fs2[i]=-2*S*S;
            fs3[i]=S;
        }
        poly gs1(t.size()),gs2(t.size()),gs3(t.size());
        rep(i,t.size()){
            mint T=get(t[t.size()-i-1]);
            gs1[i]=T;
            gs2[i]=T*T;
            gs3[i]=T*T*T;
        }
        auto h=fs1*gs1+fs2*gs2+fs3*gs3;
        vc<int>pos;
        REP(i,t.size()-1,s.size()){
            if(h[i].val)res[i-t.size()+1]=0;
        }
    }
    vc<int>pos;rep(i,res.size())if(res[i])pos.pb(i);
    return pos;
}