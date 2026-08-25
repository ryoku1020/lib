#pragma once
#include"../mat.hpp"
#include"../../poly/base.hpp"
template<class T>
matrix<T>hessenberg(matrix<T>mt){
    int n=mt.size();
    if(n<=1)return mt;
    rep(j,n-1){
        REP(i,j+1,n){
            if(mt[i][j]!=0){
                if(i==j+1)break;
                swap(mt[i],mt[j+1]);
                rep(k,n){
                    swap(mt[k][i],mt[k][j+1]);
                }
                break;
            }
        }   
        if(mt[j+1][j]==0)continue;
        T dv=1/T(mt[j+1][j]);
        REP(i,j+2,n){
            if(mt[i][j]==0)continue;
            T coef=dv*mt[i][j];
            rep(k,n){
                mt[i][k]-=mt[j+1][k]*coef;
            }
            rep(k,n){
                mt[k][j+1]+=mt[k][i]*coef;
            }
        }
    }
    return mt;
}
template<class T>

fps<T>characteristic(matrix<T>mt){
    if(mt.size()==0)return fps<T>{1};
    mt=hessenberg(mt);
    int n=mt.size();
    vc<fps<T>>res(n+1);res[0]=fps<T>{1};
    res[1]=fps<T>{-mt[0][0],1};
    REP(i,2,n+1){
        res[i]+=fps<T>{-mt[i-1][i-1],1}*res[i-1];
        T ml=mt[i-1][i-2];
        drep(j,i-1){
            res[i]-=mt[j][i-1]*ml*res[j];
            if(j)ml*=mt[j][j-1];
        }
    }
    return res[n];
}