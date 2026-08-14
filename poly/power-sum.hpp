#pragma once
#include"base.hpp"
template<class mint>
//res[k]:= sum c_j a_j^k
vc<mint>PowerSum(vc<mint>a,vc<mint>c,int K){
    using f=fps<mint>;
    int n=a.size();
    if(n==0)return vc<mint>(K+1);
    vc<f>fs(n);rep(i,n)fs[i]={1,-a[i]};
    auto dfs=[&](auto&dfs,int l,int r)->pair<f,f>{
        if(r-l==1){
            return {{c[l]},{1,-a[l]}};
        }
        int mid=l+r>>1;
        auto A=dfs(dfs,l,mid);
        auto B=dfs(dfs,mid,r);
        auto nq=A.second*B.second;
        auto np=A.second*B.first+A.first*B.second;
        return{np,nq};
    };
    auto res=dfs(dfs,0,n);
    res.first*=res.second.inv(K+1);
    res.first.resize(K+1);
    return res.first;
}
