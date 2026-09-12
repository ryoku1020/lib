#pragma once
#include"../convolution/conv.hpp"
#include"../modular/multi-discrete.hpp"
#include"../modular/primitive-root.hpp"

template<class mint>
vc<mint>convolutionp(vc<mint>a,vc<mint>b,ll p){
    assert(a.size()==b.size()&&a.size()==p);
    ll g=primitive_root(p);
    vc<ll>i1d(p-1);iota(all(i1d),1);
    vc<ll>e=multidiscrete(p,g,i1d);
    vc<mint>res(p);
    res[0]+=sum<mint,mint>(a)*b[0]+sum<mint,mint>(b)*a[0]-a[0]*b[0];
    a.erase(a.begin());b.erase(b.begin());
    vc<mint>na(p-1),nb(p-1);
    rep(i,p-1)na[e[i]]=a[i],nb[e[i]]=b[i];
    na=atcoder::convolution(na,nb);
    REP(i,p-1,na.size())na[i%(p-1)]+=na[i];
    ll idx=1;
    rep(i,p-1){
        res[idx]+=na[i];
        idx*=g;idx%=p;
    }
    return res;
}
