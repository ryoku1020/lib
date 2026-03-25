#pragma once
#include"../template.hpp"
template<class X>
struct PotentialUnionFind{
    using value_type=typename X::value_type;
    vc<int>par;
    //val[par[x]]=val[x]*w[x]
    vc<value_type>w;
    PotentialUnionFind(int n):par(n,-1),w(n,X::e()){}
    int root(int x){
        if(par[x]<0)return x;
        else{
            auto res=root(par[x]);
            w[x]=X::op(w[x],w[par[x]]);
            return par[x]=res;
        }
    }
    int same(int x,int y){
        return root(x)==root(y);
    }
    //assume that same(x,y)=1
    //val[x]^{-1}*val[y] 
    value_type diff(int x,int y){
        assert(same(x,y));
        return X::op(w[x],X::inv(w[y]));
    }
    //val[x]=val[y]*W 
    int merge(int x,int y,value_type W){
        if(same(y,x)){
            if(diff(y,x)!=W)return -1;
            return 0;
        }
        W=X::op(X::op(X::inv(w[y]),W),w[x]);
        x=root(x),y=root(y);
        par[x]+=par[y];
        par[y]=x;
        w[y]=W;
        return 1;
    }
};