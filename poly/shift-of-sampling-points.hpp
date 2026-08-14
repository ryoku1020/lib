#pragma once
#include"base.hpp"
template<class mint>
//(0,sample[0])(1,sample[1])... を満たす deg(f)<n なる f について、f(t+0)...f(t+m-1) を列挙
vc<mint>ShiftofSamplingPoints(int n,int t,int m,vc<mint>sample){
    using B=Binom<mint>;
    using fps=fps<mint>;
    fps a1(n);rep(i,n)a1[i]=sample[i]*(i%2?-1:1)*B::invfact(i);
    fps a2(n);rep(i,n)a2[i]=B::invfact(i);
    fps a=a1*a2;
    a.resize(n);
    rep(i,n){
        if(i%2)a[i]*=-1;
        a[i]*=B::fact(i);
    }
    fps T(n);{
        mint tt=1;
        rep(i,n){
            T[i]=tt*B::invfact(i);
            tt*=t-i;
        }
    }
    reverse(all(a));
    fps tmp=a*T;
    fps f(n);rep(i,n)f[i]=tmp[n-1-i]*B::invfact(i);
    while(a2.size()<m)a2.pb(B::invfact(a2.size()));
    fps g=f*a2;
    vc<mint>res(m);
    rep(i,m)res[i]=g[i]*B::fact(i);
    return res;
}