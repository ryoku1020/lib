#pragma once
struct randf{
    mt19937 mt;
    randf():mt(chrono::steady_clock::now().time_since_epoch().count()){}
    ll operator()(){
        return mt();
    }
    ll operator()(ll l,ll r){
        assert(l<r);
        return uniform_int_distribution<ll>(l,r-1)(mt);
    }
};
