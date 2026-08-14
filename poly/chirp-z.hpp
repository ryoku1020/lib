#pragma once
#include"base.hpp"

//f(a),f(ar),...,f(ar^{m-1})
template<class mint>
vc<mint>ChirpZ(fps<mint>f,mint a,mint r,int m){
    assert(mint::get_mod());
    if(m==0)return {};
    if(r==0){
        vc<mint>ans(m);
        mint coef=1;
        rep(i,f.size()){
            ans[0]+=f[i]*coef;
            coef*=a;
        }
        REP(i,1,m)ans[i]=f[0];
        return ans;
    }
    fps<mint>A(f.size()),B(f.size()+m);
    vc<mint>ir(f.size()+m+1),rp(f.size()+m+1);
    mint tmp=1;mint IR=1;
    mint inv_r=1/r;
    rep(i,ir.size()){
        ir[i]=tmp;
        tmp*=IR;
        IR*=inv_r;
    }
    tmp=1;IR=1;
    rep(i,rp.size()){
        rp[i]=tmp;
        tmp*=IR;
        IR*=r;
    }
    mint AA=1;
    rep(i,f.size()){
        A[f.size()-i-1]=f[i]*ir[i]*AA;
        AA*=a;
    }
    rep(i,f.size()+m)B[i]=rp[i];
    auto res=A*B;
    vc<mint>ans(m);
    rep(i,m){
        ans[i]=res[i+f.size()-1]*ir[i];
    }
    return ans;
}