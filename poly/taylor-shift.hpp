#pragma once
#include"base.hpp"
template<class mint>
fps<mint>taylor_shift(fps<mint>f,int c){
    assert(mint::get_mod());
    binom<mint>bin;bin.build(f.size()+2);
    vc<mint>cp(f.size()+1);cp[0]=1;REP(i,1,f.size()+1)cp[i]=cp[i-1]*c;
    rep(i,f.size())f[i]*=bin.fact(i);
    fps<mint>rc(f.size());rep(i,f.size())rc[i]=cp[f.size()-i-1]*bin.invfact(f.size()-i-1);
    auto ans=(f*rc);
    ans=fps<mint>(ans.begin()+f.size()-1,ans.end());
    rep(i,f.size())ans[i]*=bin.invfact(i);
    return ans;
}
