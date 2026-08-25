#pragma once
#include"mod-utillity.hpp"
//x ≡ r0.first (mod r0.second)
//x ≡ r1.first (mod r1.second)
template<class T>
pair<T,T>crt(pair<T,T>r0,pair<T,T>r1){
    r0.second=abs(r0.second),r1.second=abs(r1.second);
    assert(r0.second&&r1.second);
    r0.first%=r0.second;if(r0.first<0)r0.first+=r0.second;
    r1.first%=r1.second;if(r1.first<0)r1.first+=r1.second;
    auto gcd=[&](T a,T b){
        while(b){a%=b;swap(a,b);}return a;
    };
    if(r0.second==r1.second){
        if(r0.first==r1.first)return r0;
        return{-1,-1};
    }
    T right=r1.first-r0.first;
    T g=gcd(r0.second,r1.second);
    T mod=r0.second/g*r1.second;
    if(right%g)return {-1,-1};
    right/=g;
    r0.second/=g;
    r1.second/=g;
    T x,y;
    extgcd<T>(r0.second,r1.second,x,y);
    x*=right;x%=r1.second;if(x<0)x+=r1.second;
    return {(r0.second*g*x+r0.first)%mod,mod};
}
template<class T>
pair<T,T>crt(vc<pair<T,T>>vs){
    pair<T,T>ans={0,1};
    for(auto r:vs){
        ans=crt(ans,r);
        if(ans.first==-1)return ans;
    }
    return ans;
}
