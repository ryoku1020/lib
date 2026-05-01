#pragma once
#include"../template.hpp"
#include"enumerate-floor.hpp"
ll prime_counting(ll n){
    assert(n>=0);
    auto QN=floors(n);
    vc<ll>dp(QN.size()); 
    rep(i,QN.size())dp[i]=QN[i];
    int m_val=isqrt(n);
    vector<int>id1(m_val+1),id2(m_val+1);
    for(int i=0;i<QN.size();++i){
        if(QN[i]<=m_val)id1[QN[i]]=i;
        else id2[n/QN[i]]=i;
    }
    auto get_idx=[&](ll x){return x<=m_val?id1[x]:id2[n/x];};
    vc<int>primes;
    for(ll x=2;x<=m_val;x++){
        if(dp[x-1]>dp[x-2]){
            primes.pb(x);
            for(int i=(int)QN.size()-1;i>=0;--i){
                auto&v=QN[i];
                if(x*x>v)break;
                dp[i]-=(dp[get_idx(v/x)]-dp[x-2]);
            }
        }
    }
    return dp.back()-1;
}
