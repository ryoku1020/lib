#pragma once
template<class X>
struct SparseTable{
    using V=typename X::value_type;
    int lg;
    int n;
    vvc<V>table;
    bool built=false;
    SparseTable(int N){
        assert(N>=0);
        lg=0;
        while((1<<lg)<=N)lg++;
        lg--;
        n=N;
        table=vvc<V>(lg+1,vc<V>(n,X::e()));
    }
    void set(int i,V x){
        assert(0<=i&&i<n);
        table[0][i]=x;
        built=false;
    }
    void build(){
        if(built)return;
        built=true;
        REP(i,1,lg+1){
            rep(j,n){
                if(j+(1<<i)>n)break;
                table[i][j]=X::op(table[i-1][j],table[i-1][j+(1<<(i-1))]);
            }
        }
    }
    V prod(int l,int r){
        assert(0<=l&&l<=r&&r<=n);
        build();
        if(l==r)return X::e();
        int i=31-__builtin_clz(r-l);
        return X::op(table[i][l],table[i][r-(1<<i)]);
    }
};
