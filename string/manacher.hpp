#pragma once
#include"../template.hpp"
template<class String>
vc<int>Manacher(String&s){
    assert(s.size()<=numeric_limits<int>::max()/2);
    if(s.empty())return {};
    if(s.size()==1)return {1};
    vc<int>S;
    rep(i,(int)s.size()){
        S.push_back(numeric_limits<int>::min());S.push_back(s[i]);
    }
    S.pb(numeric_limits<int>::min());
    int n=S.size();vc<int>dp(n);
    int mid=0,r=0;
    while(mid<n){
        while(mid-r>=0&&mid+r<n&&S[mid-r]==S[mid+r])r++;
        dp[mid]=r;
        int k=1;
        while(mid-k>=0&&dp[mid-k]+k<dp[mid])dp[mid+k]=dp[mid-k],k++;
        mid+=k;
        r-=k;
    }
    dp.erase(dp.begin());
    dp.pop_back();
    rep(i,dp.size()){
        dp[i]--;
    }
    return dp;
}
