#pragma once
template<class T>
struct pointaddO1{
    vc<T>block;
    vc<T>val;
    int B;
    pointaddO1(){}
    pointaddO1(int n):val(n){
        build();
    }
    pointaddO1(const vc<T>&a):val(a){
        build();
    }
    void build(){
        B=max<int>(1,sqrt(val.size())*0.5);
        block.resize((val.size()+B-1)/B);
        rep(i,val.size())block[i/B]+=val[i];
    }
    void add(int i,T x){
        assert(0<=i&&i<val.size());
        val[i]+=x;
        block[i/B]+=x;
    }
    T query(int l,int r){
        assert(0<=l&&l<=r&&r<=val.size());
        int bl=l/B,br=r/B;
        T res{};
        if(bl==br){
            REP(i,l,r)res+=val[i];
            return res;
        }
        REP(i,l,(bl+1)*B)res+=val[i];
        REP(i,bl+1,br)res+=block[i];
        REP(i,br*B,r)res+=val[i];
        return res;
    }
};