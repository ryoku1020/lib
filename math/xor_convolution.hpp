#pragma once
#include"../template.hpp"
template<class mint>
void fwht(vc<mint>&a){
    assert(mint::get_mod());
    int n=a.size();
    for(int h=1;h<n;h*=2){
        for(int i=0;i<n;i+=h*2){
            REP(j,i,i+h){
                mint x1=a[j];
                mint x2=a[j+h];
                a[j]=x1+x2;
                a[j+h]=x1-x2;
            }
        }
    }
}
template<class mint>
vc<mint>xor_convolution(vc<mint>a,vc<mint>b){
    int N=max(a.size(),b.size());
    int lg=0;while((1<<lg)<N)lg++;
    a.resize(1<<lg);
    b.resize(1<<lg);
    fwht(a);
    fwht(b);
    rep(i,1<<lg)a[i]*=b[i];
    fwht(a);
    mint iv=1/mint(2).pow(lg);
    rep(i,1<<lg)a[i]*=iv;
    return a;
}