#pragma  once
#ifndef FLOORS_FUNCTION
#define FLOORS_FUNCTION
vc<ll>floors(ll n){
    assert(n>=0);
    if(n==0)return {};
    vc<ll>res;
    ll m=isqrt(n);
    REP(i,1,m+1)res.pb(i);
    DREP(i,m,1)if(n/i>m)res.pb(n/i);
    return res;
}
#endif
vc<array<ll,3>>segment_floor(ll N,ll m){
    auto res=floors(N);
    if(N==0)return {{1,m+1,0}};
    reverse(all(res));
    vc<array<ll,3>>ret;
    ret.pb({1,2,N});
    rep(i,(int)res.size()-1){
        ret.pb({N/res[i]+1,N/res[i+1]+1,res[i+1]});
    }
    ret.pb({N/res.back()+1,m+1,0});
    return ret;
}
