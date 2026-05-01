#pragma once
#include"../template.hpp"
template<class String>
vc<int>ZAlgorithm(String&s){
    assert(s.size()<=numeric_limits<int>::max());
    int N=s.size();
    vc<int>dp(N);
    dp[0]=N;
    int l=1,r=0;
    while(l<N){
        while(l+r<N&&s[l+r]==s[r])++r;
        dp[l]=r;
        if(dp[l]==0){
            ++l;
            continue;
        }
        int k=1;
        while(k+dp[k]<dp[l]&&l+k<N)dp[l+k]=dp[k],++k;
        l+=k,r-=k;
    }
    return dp;
}
