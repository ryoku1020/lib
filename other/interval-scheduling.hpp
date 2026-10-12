#pragma once
template<class T>
//[l[i],r[i]) を cover 
vc<int>interval_scheduling(vc<T>l,vc<T>r){
    assert(l.size()==r.size());
    auto idx=argsort<T,1>(r);
    T used_last=-inf<T>;
    vc<int>res;
    for(auto&i:idx){
        if(used_last<=l[i]){
            res.pb(i);
            used_last=r[i];
        }
    }
    return res;
}