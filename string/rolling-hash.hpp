#pragma once
#include "../ds/utility/hash.hpp"
#include "../math/modular/mod261.hpp"

template<int N=1>
struct rolling_hash{
    using H=hash_type<mod261_int,N>;
    inline static const H base=H::get_base();
    inline static vector<H>pows={H(1)};
    inline static vector<H>ipows={H(1)};
    vector<H>sum;

    rolling_hash(){}
    template<class Container>
    rolling_hash(const Container&s){build(s);}

    static void extend(int n){
        while((int)pows.size()<=n){
            pows.pb(pows.back()*base);
            ipows.pb(ipows.back()/base);
        }
    }
    static H pow(int n){
        extend(n);
        return pows[n];
    }
    static H ipow(int n){
        extend(n);
        return ipows[n];
    }
    template<class Container>
    void build(const Container&s){
        int n=s.size();
        extend(n);
        sum.assign(n+1,H(0));
        for(int i=0;i<n;++i)sum[i+1]=sum[i]+H(s[i])*pow(i);
    }
    H get(int l,int r)const{
        assert(0<=l&&l<=r&&r<(int)sum.size());
        return (sum[r]-sum[l])*ipow(l);
    }
    static H add(H hash,int len,const H&x){
        return hash+x*pow(len);
    }
};
