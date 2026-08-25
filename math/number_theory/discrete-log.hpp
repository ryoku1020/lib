#pragma once
#include"../modular/mod-utillity.hpp"
//coef*x^k ≡ y mod m なる min k 
ll discrete_log(ll coef,ll x,ll y,ll m){
    x%=m,y%=m,coef%=m;
    if(m==1)return 0;
    if(y==1)return 0;
    if(coef==0){
        if(y==0)return 0;
        return -1;
    }
    ll g;
    ll slide=0;
    while((g=gcd(x,m))!=1){
        if(y%g)return -1;
        slide++;
        coef*=x/g;
        y/=g,m/=g;coef%=m;
        if(coef==y)return slide;
    }
    if(m==1){
        return slide;
    }
    coef%=m;
    ll cval=coef;
    y*=(inv(cval,m).first+m)%m;y%=m;
    //coef x^{k-slide} ≡ y mod m
    auto bsgs=[&](ll x,ll y,ll m)->ll{
        ll sm=isqrt(m)+1;
        ll bxp=1;
        ll ixp=1;
        ll ix=(inv(x,m).first+m)%m;
        unordered_map<ll,ll>dp;
        rep(i,sm){
            if(!dp.count((y*ixp)%m)){
                dp[(y*ixp)%m]=i;
            }
            ixp*=ix;ixp%=m;
            bxp*=x;bxp%=m;
        }
        ll bxpp=1;
        rep(i,sm+1){
            if(dp.count(bxpp%m)){
                return dp[bxpp%m]+i*sm;
            }
            bxpp*=bxp;bxpp%=m;
        }
        return -1;
    };
    ll mk=bsgs(x,y,m);if(mk<0)return -1;mk+=slide;
    return mk;
}
