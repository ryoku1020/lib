#pragma once
#include"../template.cpp"
#include"persisitent_array.cpp"
template<int B>
struct persisitent_uf{
    persisitent_array<int,B> par;
    using node=persisitent_array<int,B>::Node*;
    node build(int n){
        return par.build(n,-1);
    }
    int root(int x,node root_){
        auto res=par.get(x,root_);
        if(res<0)return x;
        return root(res,root_);
    }
    int same(int a,int b,node root_){
        a=root(a,root_);
        b=root(b,root_);
        return a==b;
    }
    node merge(int a,int b,node root_){
        a=root(a,root_),b=root(b,root_);
        if(a==b)return root_;
        int pa=par.get(a,root_);
        int pb=par.get(b,root_);
        if(-pa<-pb)swap(a,b),swap(pa,pb);
        node res;
        res=par.change(a,pa+pb,root_);
        res=par.change(b,a,res);
        return res;
    }
};