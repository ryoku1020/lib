#pragma once
#include"../template.cpp"
template<class X>
struct sparse_table{
    using V=typename X::value_type;
    int lg;
    int n;
    vvc<V>table;
    sparse_table(int N){
        lg=0;
        while((1<<lg)<=N)lg++;
        lg--;
        n=N;
        table=vvc<V>(lg+1,vc<V>(n,X::e()));
    }
    void set(int i,V x){
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
        if(l==r)return X::e();
        for(int i=0;;i++){
            if((r-l)<(1<<(i+1))){
                return X::op(table[i][l],table[i][r-(1<<i)]);
            }
        }
    }
};