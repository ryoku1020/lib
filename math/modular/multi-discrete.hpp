#pragma once
#include"dynamic-modint64.hpp"
#include"../../ds/ordered/hashmap.hpp"

vc<ll>multidiscrete(ll p,ll g,vc<ll>a){
    using mint=dynamic_modint64<20260827>;
    if(a.empty())return {};
    mint::set_mod(p);
    int n=a.size();
    ll b=(ll)(sqrtl((ld)n*p)*0.55L)+1;
    hashmap<ll,ll>hm;
    hm.reserve(b);
    mint mg=mint::raw(g);
    mint ig=1;
    rep(i,b){
        hm[ig.val]=i;
        ig*=mg;
    }
    mint iig=ig.inv();
    mint eg=1;
    vc<ll>ans(n,-1);
    int left=n;
    for(ll i=0;i*b<p-1&&left;i++){
        rep(j,n){
            if(ans[j]>=0)continue;
            mint target=mint::raw(a[j])*eg;
            if(hm.count(target.val)){
                ans[j]=(hm[target.val]+i*b)%(p-1);
                left--;
            }
        }
        eg*=iig;
    }
    return ans;
}