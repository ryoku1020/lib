#pragma once
#include"../poly/shift-of-sampling-points.hpp"
template<class mint>
struct SuperFactorial{
    static const int mod=mint::get_mod();
    static const int K=1<<9;
    vc<mint>pre_calc;
    SuperFactorial(){
        int need=(mod-1)/K;
        vc<mint>f{1};
        mint pow2=1;
        while(f.size()<K){
            int n=f.size();
            auto g=ShiftofSamplingPoints(n,n,3*n,f);
            for(auto&x:g)f.pb(x);
            vc<mint>nf(n*2);
            rep(i,n*2)nf[i]=f[2*i]*f[2*i+1]*pow2*(2*i+1);
            f=move(nf);
            pow2*=2;
        }
        auto G=ShiftofSamplingPoints(f.size(),f.size(),need-f.size(),f);
        for(auto&x:G)f.pb(x);
        pre_calc.assign(need+1,1);
        rep(i,need){
            pre_calc[i+1]=pre_calc[i]*f[i]*mint((ll)(i+1)*K);
        }
    }
    mint query(ll k){
        if(k>=mod)return 0;
        mint now=pre_calc[k/K];
        for(ll l=k/K*K+1;l<=k;l++)now*=l;
        return now;
    }
};
