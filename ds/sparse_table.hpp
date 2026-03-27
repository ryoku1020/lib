#pragma once
#include "../template.hpp"
template<class X>
struct SparseTable{
    using V=typename X::value_type;
    int lg;
    int n;
    vvc<V>table;
    SparseTable(int N){
        lg=0;
        while((1<<lg)<=N)lg++;
        lg--;
        n=N;
        table=vvc<V>(lg+1,vc<V>(n,X::e()));
    }
    void set(int i,V x){
        assert(0<=i&&i<n);
        table[0][i]=x;
    }
    void build(){
        REP(i,1,lg+1){
            rep(j,n){
                if(j+(1<<i)>n)break;
                table[i][j]=X::op(table[i-1][j],table[i-1][j+(1<<(i-1))]);
            }
        }
    }
    V prod(int l,int r){
        assert(0<=l&&l<=r&&r<=n);
        if(l==r)return X::e();
        for(int i=0;;i++){
            if((r-l)<(1<<(i+1))){
                return X::op(table[i][l],table[i][r-(1<<i)]);
            }
        }
    }
};