#pragma once
#include"../ds/sequence/BIT.hpp"
#include"../d
template<class T>
ll inversion(vc<T>a){
    compresser<ll>cp;for(auto x:a)cp.push(x);
    for(auto&x:a)x=cp.find(x);
    ll ans=0;
    binary_indexed_tree<int>bit(a.size());
    rep(i,a.size()){
        ans+=bit.sum(a[i]+1,a.size());bit.add(a[i],1);
    }
    return ans;
}