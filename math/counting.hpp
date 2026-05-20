#pragma once
#include"fps.hpp"
//[x^{0,1,..,size}] (1+x^s[0])(1+x^s[1])... 
vc<mint>EnumarateProd(vc<int>s,int size){
    assert(size>=0);
    assert(all_of(all(s),[](int x){return x>0;}));
    if(s.empty())return poly(size).exp(size);
    Binom<mint>B;B.build(size+1);
    int S=max(s);
    vc<mint>cnt(S+1);for(auto&x:s)cnt[x]+=1;
    poly cnt2(size);for(int i=1;i<size;i++)if(i<=S&&cnt[i].val)for(int j=i;j<size;j+=i){
        cnt2[j]+=cnt[i]*B.invfact(j/i)*B.fact(j/i-1)*(j/i%2?1:-1);
    }
    return cnt2.exp(size);
}

//[x^{0,1,..,size}] 1/(1-x^s[0])(1-x^s[1])... 
vc<mint>EnumarateProdInv(vc<int>s,int size){
    assert(size>=0);
    assert(all_of(all(s),[](int x){return x>0;}));
    if(s.empty())return poly(size).exp(size);
    Binom<mint>B;B.build(size+1);
    int S=max(s);
    vc<mint>cnt(S+1);for(auto&x:s)cnt[x]+=1;
    poly cnt2(size);for(int i=1;i<size;i++)if(i<=S&&cnt[i].val)for(int j=i;j<size;j+=i){
        cnt2[j]+=cnt[i]*B.invfact(j/i)*B.fact(j/i-1);
    }
    return cnt2.exp(size);
}
vc<mint>PartitionFunction(int n){
    assert(n>=0);
    if(n==0)return {1};
    vc<int>s(n);iota(all(s),1);
    return EnumarateProdInv(s,n+1);
}
