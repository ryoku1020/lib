#pragma once
#include"../template.hpp"
struct ConvexHullTrick{
    using P=pair<ll,ll>;
    vc<P>node;
    vc<ll>xs;
    int n;
    ll eval(P p,ll x){
        return p.first*x+p.second;
    }
    ConvexHullTrick(vc<ll>x){
        if(x.empty())x.push_back(0);
        int N=x.size();
        n=1;
        while(n<N)n*=2;
        rep(i,N)xs.push_back(x[i]);
        while(xs.size()<n)xs.push_back(xs.back()+1);
        node=vc<P>(n*2,{0,4e18});
    }
    void add(int L,int R,int idx,P p){
        int mid=L+R>>1;
        int mb=eval(node[idx],xs[mid])>eval(p,xs[mid]);
        int lb=eval(node[idx],xs[L])>eval(p,xs[L]);
        if(mb)swap(node[idx],p);
        if(L+1>=R)return;
        if(lb!=mb)add(L,mid,idx*2,p);
        else add(mid,R,idx*2+1,p);
    }
    void add_line(P p){
        add(0,n,1,p);
    }
    ll get(ll x){
        ll X=xs[x];
        ll res=eval(node[x+=n],X);
        while(x>>=1)chmin(res,eval(node[x],X));
        return res;
    }
};