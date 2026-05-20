#pragma once
#include "lazy-segtree.hpp"

//T > 長方形の max T2> ans の max
template<class T>
struct RectangleUnion{
    struct M{
        using value_type=pair<int,T>;
        static value_type op(value_type a,value_type b){
            if(a.first==b.first)return {a.first,a.second+b.second};
            return min(a,b);
        }
        static value_type e(){
            return {2e9,0};
        }
    };
    struct MM{
        using value_type=M::value_type;
        using lazy_type=int;
        static value_type Apply(value_type a,lazy_type b){
            return {a.first+b,a.second};
        }
        static lazy_type Merge(lazy_type a,lazy_type b){
            return a+b;
        }
        static lazy_type id(){
            return 0;
        }
    };
    struct Rec{
        T l,r,d,u;
    };
    vc<Rec>rec;
    vc<Rec>rec2;
    void reserve(int n){
        rec.reserve(n);
    }
    void add_rectangle(T l,T r,T d,T u){
        assert(l<r&&d<u);
        rec.pb({l,r,d,u});
    }
    template<class T2> 
    T2 calc(){
        Compress<T>x;
        x.v.reserve(rec.size()*2);
        for(auto&[l,r,d,u]:rec){
            x.push(l);
            x.push(r);
        }
        x.work();
        vc<int>xl(rec.size()),xr(rec.size());rep(i,rec.size())xl[i]=x.find(rec[i].l),xr[i]=x.find(rec[i].r);
        vc<tuple<T,int,int>>iord(rec.size()*2);rep(i,rec.size()){
            iord[i*2]={rec[i].d,i,1};
            iord[i*2+1]={rec[i].u,i,-1};
        }
        sort(all(iord));
        vc<pair<int,T>>w(x.size()-1);rep(i,x.size()-1)w[i]={0,x.v[i+1]-x.v[i]};
        LazySegtree<M,MM>segtree(x.size()-1,w);
        T pre=get<2>(iord[0]);
        T2 ans=0;
        for(auto&[ypos,i,diff]:iord){
            auto res=segtree.all_prod();
            T W=x.v.back()-x.v[0];
            if(res.first==0)W-=res.second;
            ans+=T2(W)*(-pre+ypos);
            segtree.apply(xl[i],xr[i],diff);
            pre=ypos;
        }
        return ans;
    }
};
