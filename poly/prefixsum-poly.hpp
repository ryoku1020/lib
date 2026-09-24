#pragma once
#include"base.hpp"
template<class mint>
fps<mint>prefixsum_poly(fps<mint>f){
    int n=f.size();
    auto B=bernoulli<mint>(n+1);
    rep(i,B.size())B[i]*=binom<mint>::invfact(i);reverse(all(B));
    rep(i,n)f[i]*=binom<mint>::fact(i);

    auto fb=f*B;
    fps<mint>ans(n+1);
    REP(i,1,n+1){
        ans[i]=fb[i+n-1]*binom<mint>::invfact(i);
    }
    return ans;
}