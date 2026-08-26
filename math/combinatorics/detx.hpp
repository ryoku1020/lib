#pragma once
#include"../mat.hpp"
#include"../../poly/base.hpp"
#include"../rand.hpp"
//det(m0+m1x)
template<class T>
fps<T>detx(matrix<T>m0,matrix<T>m1){
    randf rn; 
    rep(t,2){
        T shift=rn();
        matrix<T>nm0=m1;
        matrix<T>nm1=m0+shift*m1;
        T dm1=nm1.det();
        if(dm1==0)continue;
        matrix<T>im1=nm1.inverse().value();
        auto nm01=nm0*im1;
        fps<T>ans=characteristic<T>(-nm01)*dm1;
        ans.resize(m0.size()+1);
        reverse(all(ans));
        ans=taylor_shift(ans,int(-shift.val));
        return ans;
    }
    return fps<T>(m0.size()+1);
}