#pragma  once
#include"../template.hpp"

vc<ll>floors(ll n){
    assert(n>=0);
    if(n==0)return {};
    vc<ll>res;
    ll m=isqrt(n);
    REP(i,1,m+1)res.pb(i);
    DREP(i,m,1)if(n/i>m)res.pb(n/i);
    return res;
}