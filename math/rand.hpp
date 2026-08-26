#pragma once
#include <random>
struct randf{
    mt19937_64 mt;
    randf():mt(chrono::steady_clock::now().time_since_epoch().count()){}
    ull operator()(){
        return mt();
    }
    ull operator()(ll l,ll r){
        assert(l<r);
        return uniform_int_distribution<ll>(l,r-1)(mt);
    }
};
