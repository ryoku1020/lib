#pragma once
#include"segtree.hpp"
template<class T>
struct rangeadd_rangemin{
    struct Info{
        struct S{
            T sum;
            T min;
        };
        using value_type=S;
        static S op(S a,S b){
            return S{a.sum+b.sum,min(a.min,a.sum+b.min)};
        }
        static S e(){
            return S{0,inf<T>};
        }
    };
    int n;
    segtree<Info>seg;
    rangeadd_rangemin(){}
    rangeadd_rangemin(int n):n(n),seg(n){}
    template<class F>rangeadd_rangemin(const vc<F>&v){
        n=v.size();
        vc<typename Info::S>dat(n);
        rep(i,n){
            T x=v[i]-(i?v[i-1]:0);
            dat[i]={x,x};
        }
        seg=segtree<Info>(dat);
    }
    void add(int l,int r,T x){
        assert(0<=l&&l<=r&&r<=n);
        auto s=seg.prod(l,l+1);
        s.sum+=x;
        s.min=s.sum;
        seg.set(l,s);
        if(r<n){
            s=seg.prod(r,r+1);
            s.sum-=x;
            s.min=s.sum;
            seg.set(r,s);
        }
    }
    T getmin(int l,int r){
        assert(0<=l&&l<=r&&r<=n);
        return seg.prod(0,l).sum+seg.prod(l,r).min;
    }
};