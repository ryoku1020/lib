#pragma once
#include"../../template.hpp"
namespace ryoku{
// f[0]=g[0]=0を仮定する
template<class mint,class F>
void online_subset_convolution(int n,F getfg){
    vvc<mint>f(n+1,vc<mint>(1<<n));
    vvc<mint>g(n+1,vc<mint>(1<<n));
    auto zeta=[&](vc<mint>&v){
        int m=1<<n;
        for(int b=1;b<m;b<<=1){
            for(int j=0;j<m;j+=b*2){
                rep(t,b)v[j+b+t]+=v[j+t];
            }
        }
    };
    auto mobius=[&](vc<mint>&v){
        int m=1<<n;
        for(int b=1;b<m;b<<=1){
            for(int j=0;j<m;j+=b*2){
                rep(t,b)v[j+b+t]-=v[j+t];
            }
        }
    };
    REP(k,1,n+1){
        vc<mint>h(1<<n);
        rep(l,k+1)rep(S,1<<n){
            h[S]+=f[l][S]*g[k-l][S];
        }
        mobius(h);
        rep(S,1<<n){
            if(popcount(S)!=k)continue;
            auto FG=getfg(S,h[S]);
            f[k][S]=FG.fi;
            g[k][S]=FG.se;
        }
        if(k<n){
            if(k>=n-6){
                rep(S,1<<n){
                    if(popcount(S)!=k)continue;
                    mint x=f[k][S],y=g[k][S];
                    int rem=((1<<n)-1)^S;
                    for(int T=rem;T;T=(T-1)&rem){
                        f[k][S|T]+=x;
                        g[k][S|T]+=y;
                    }
                }
            }else{
                zeta(f[k]),zeta(g[k]);
            }
        }
    }
}

}
