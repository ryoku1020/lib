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

//[n,0] ... [n,n]
template<class mint>
vc<mint>Stirling1(int n){
    auto dfs=[&](auto&dfs,int n)->poly{
        if(n==1){
            return {0,1};
        }
        if(n<=0)return {1};
        if(n%2==0){
            auto poly1=dfs(dfs,n/2);
            auto poly2=taylor_shift(poly1,-n/2);
            return poly1*poly2;
        }
        return dfs(dfs,n-1)*poly{-n+1,1};
    };
    auto ans=dfs(dfs,n);
    return ans;
}
//[k,k] ... [n,k]
template<class mint>
vc<mint>Stirling1FixedK(int n,int k){
    using B=Binom<mint>;
    poly f=-((poly{1,-1}).log(n+1).pow(k,n+1))*B::invfact(k);
    poly ans(n-k+1);
    rep(i,n-k+1){
        ans[i]=f[i+k]*B::fact(i+k)*((i+k)%2?1:-1);
    }
    return ans;
}
//{n,0} ... {n,n}
//{i,k} :=i 個のものを k 個の非空グループに分ける場合の数
template<class mint>
vc<mint>Stirling2(int n){
    using B=Binom<mint>;
    vc<mint>f1(n+1),f2(n+1);
    rep(i,n+1){
        f1[i]=mint(i).pow(n)*B::invfact(i);
        f2[i]=(i%2?-1:1)*B::invfact(i);
    }
    auto res=fps(f1)*fps(f2);
    return vc<mint>(res.begin(),res.begin()+n+1);
}
//{k,k} ... {n,k}
//{i,k} :=i 個のものを k 個の非空グループに分ける場合の数
template<class mint>
vc<mint>Stirling2FixedK(int n,int k){
    assert(k<=n+1);
    using B=Binom<mint>;
    fps<mint>f(n+1);rep(i,n+1)f[i]=B::invfact(i);
    f[0]-=1;
    f=f.pow(k,n+1);f*=B::invfact(k);
    rep(i,f.size())f[i]*=B::fact(i);
    return vc<mint>(f.begin()+k,f.begin()+n+1);
}