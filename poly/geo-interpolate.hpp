#pragma once
#include"base.hpp"
//f(a)=y_0 f(ar)=y_1 .... 
template<class mint>
vc<mint>geo_interporate(mint a,mint r,vc<mint>y){
    assert(mint::get_mod());
    int n=y.size();
    if(n==0)return {};
    if(n==1)return {y[0]};
    if(r==0){
        mint c0=y[1];
        mint c1=(y[0]-y[1])/a;
        return {c0,c1};
    }
    //(x-a)(x-ar)...(x-ar^{n-1})
    auto get=[&](auto&get,int n)->fps<mint>{
        if(n==0)return {1};
        auto down=get(get,n/2);
        auto res=down*down.substitute(1/r.pow(n/2))*r.pow(1ll*(n/2)*(n/2));
        if(n%2)res*={-a*r.pow(n-1),1};
        return res;
    };
    auto all_mul=get(get,n);
    auto gdeval=chirp_z(all_mul.diff(),a,r,n);
    fps<mint>A(n);rep(i,n)A[i]=y[i]/gdeval[i];
    auto coef=chirp_z(-A,r.inv(),r.inv(),n);
    fps<mint>C(n);rep(i,n)C[i]=coef[i];
    C=C.substitute(1/a);C/=a;
    return (C*all_mul).pre(n);
}
