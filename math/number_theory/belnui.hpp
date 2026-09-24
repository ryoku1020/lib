#pragma once
#include"../modular/binom.hpp"
#include"../../poly/base.hpp"
//B_n^{-}
//[1,-1/2,1/6,0,-1/30,0,5/66,0,...]
template<class mint>
vc<mint>bernoulli(int n){
    fps<mint>g(n);rep(i,n)g[i]=binom<mint>::invfact(i+1);
    g=g.inv(n);
    rep(i,n)g[i]*=binom<mint>::fact(i);
    return g;
}