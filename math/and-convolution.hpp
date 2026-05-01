#pragma once
#include"../template.hpp"
template<class mint>
vc<mint>and_convolution(vc<mint>a,vc<mint>b){
    assert(mint::get_mod());
    int N=max(a.size(),b.size());
    int lg=0;while((1<<lg)<N)lg++;
    a.resize(1<<lg);
    b.resize(1<<lg);
    auto zeta_mobius=[&](vc<mint>&a,int coef){
        rep(j,lg)rep(i,1<<lg){
            if(~i>>j&1){
                a[i]+=a[i^(1<<j)]*coef;
            }
        }
    };
    zeta_mobius(a,1);
    zeta_mobius(b,1);
    rep(i,1<<lg)a[i]*=b[i];
    zeta_mobius(a,-1);
    return a;
}
