#pragma once
#include"../number_theory/factorize.hpp"
ll primitive_root(ll p){
    assert(p>=2);
    static mt19937 mt(random_device{}());
    auto ps=factorize(p-1);
    while(1){
        ll g=mt()%(p-1)+1;
        ll ok=1;
        for(auto&[P,e]:ps){
            if(modpow<i128>(g,(p-1)/P,p)==1)ok=0;
        }
        if(ok)return g;
    }
}
