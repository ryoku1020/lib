#pragma once
#include "template.hpp"
template<class T>
struct CoordinateCompression{
    vector<T>data;
    CoordinateCompression(){}
    CoordinateCompression(int n){
        data.reserve(n);
    }
    void push(T x){
        data.push_back(x);
    }
    void co(){
        sort(data.begin(),data.end());
        data.erase(unique(data.begin(),data.end()),data.end());
    }
    int get(T x){
        auto itr=lower_bound(data.begin(),data.end(),x);
        if(itr==data.end())return -1;
        return itr-data.begin();
    }
};