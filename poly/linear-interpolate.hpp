#pragma once
#include"../math/modular/binom.hpp"
template<class mint>
//f(i)=y[i] なる deg(f)<n の f について f(v) を求める
mint linear_interpolate(int n,const vc<mint>&y,mint v){
    using B=binom<mint>;
    if(v.val<n)return y[v.val];
    vc<mint>pre(n+1,1);
    rep(i,n)pre[i+1]=pre[i]*(v-i);
    mint suf=1,res=0;
    drep(i,n){
        mint over=pre[i]*suf;
        mint under=B::invfact(i)*B::invfact(n-i-1);
        if((n-i-1)&1)over*=-1;
        res+=y[i]*over*under;
        suf*=(v-i);
    }
    return res;
}