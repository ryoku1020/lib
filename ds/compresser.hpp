#pragma once
#include"../template.hpp"
template<class T>
struct Compresser{
    vc<T>x;
    Compresser(int n){x.reserve(n);}
    Compresser(const vc<T>&xs){
        x=xs;
    }
    void push(T p){x.pb(p);}
    bool built=false;
    void build(){
        if(!chmax(built,1))return;
        sort(all(x));
        x.erase(unique(all(x)),x.end());
    }
    int find(T v){
        build();
        auto itr=lower_bound(all(x),v)-x.begin();
        if(itr==x.size()||x[itr]!=v)return -1;
        return itr;
    }
    int find_next(T v){
        build();
        return lower_bound(all(x),v)-x.begin();
    }
    int size(){
        build();
        return x.size();
    }
    T operator[](int i)const{
        assert(0<=i&&i<x.size());
        return x[i];
    }
};