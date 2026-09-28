#pragma once
#include"../arithmetic/Number.hpp"
//[100,1,2,3,4,5,6] -> [100,21,12,9,4,5,6]
template<class T>
void multiple_zeta(vc<T>&a){
    int n=a.size()-1;
    sieve::build(n);
    REP(p,2,n+1)if(sieve::is_prime(p)){
        for(int i=n/p;i>=1;i--){
            a[i]+=a[i*p];
        }
    }
    return;
}
//[100,21,12,9,4,5,6] -> [100,1,2,3,4,5,6]
template<class T>
void multiple_mobius(vc<T>&a){
    int n=a.size()-1;
    sieve::build(n);
    REP(p,2,n+1)if(sieve::is_prime(p)){
        REP(i,1,n/p+1){
            a[i]-=a[i*p];
        }
    }
    return;
}
//[100,1,2,3,4,5,6] -> [100,1,3,4,7,6,12]
template<class T>
void divisor_zeta(vc<T>&a){
    int n=a.size()-1;
    sieve::build(n);
    REP(p,2,n+1)if(sieve::is_prime(p)){
        REP(i,1,n/p+1){
            a[i*p]+=a[i];
        }
    }
    return;
}
//[100,1,3,4,7,6,12] -> [100,1,2,3,4,5,6]
template<class T>
void divisor_mobius(vc<T>&a){
    int n=a.size()-1;
    sieve::build(n);
    REP(p,2,n+1)if(sieve::is_prime(p)){
        for(int i=n/p;i>=1;i--){
            a[i*p]-=a[i];
        }
    }
    return;
}