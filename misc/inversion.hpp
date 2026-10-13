#pragma once
#include"../ds/sequence/BIT.hpp"
#include"../ds/compress.hpp"
namespace ryoku{
template<class T>
ll inversion(vc<T>a){
    compresser<T>cp;for(auto x:a)cp.push(x);
    ll ans=0;
    binary_indexed_tree<int>bit(a.size());
    rep(i,a.size()){
        int p=cp.find(a[i]);
        ans+=bit.sum(p+1,a.size());bit.add(p,1);
    }
    return ans;
}
}
