#pragma once
#include "../template.hpp"
/*
struct X{
    using value_type=pair<mint,mint>;
    static value_type op(value_type a,value_type b){
        return {a.first*b.first,b.first*a.second+b.second};
    }
    static value_type e(){
        return {1,0};
    }
    static value_type leaf(){
        return e();
    }
};*/
template<typename Info>
struct SegmentTree{
    using value_type=typename Info::value_type;
    vc<value_type>node;
    int N;
    int lg;
    void update(int i){
        assert(0<=i&&i<N);
        node[i]=Info::op(node[i*2],node[i*2+1]);
    }
    SegmentTree(int n=0){
        N=1;
        lg=0;
        while(N<n)N*=2,++lg;
        node.resize(N*2,Info::leaf());
        DREP(i,N-1,1)update(i);
    }
    template<class F>
    SegmentTree(int n,F f){
        N=1;
        lg=0;
        while(N<n)N*=2,++lg;
        node.resize(N*2,Info::e());
        for(int i=N;i<N+n;i++){
            node[i]=f(i-N);
        }
        DREP(i,N-1,1)update(i);
    }
    void set(int i,value_type val){
        assert(0<=i&&i<N);
        node[i+=N]=val;
        while(i>>=1)update(i);
    }
    value_type prod(int l,int r){
        assert(0<=l&&l<=r&&r<=N);
        l+=N,r+=N;
        value_type sml=Info::e(),smr=Info::e();
        while(l<r){
            if(l&1)sml=Info::op(sml,node[l++]);
            if(r&1)smr=Info::op(node[--r],smr);
            l/=2,r/=2;
        }
        return Info::op(sml,smr);
    }
    value_type all_prod(){
        return node[1];
    }
    template<class F>
    int max_right(int L,F f){
        assert(0<=L&&L<=N);
        int l=N+L,w=1;
        value_type ansL=Info::e();
        for(;L+w<=N;l>>=1,w<<=1)if(l&1){
            if(!f(Info::op(ansL,node[l])))break;
            ansL=Info::op(ansL,node[l++]);
            L+=w;
        }
        while(l<<=1,w>>=1){
            if(L+w<=N&&f(Info::op(ansL,node[l]))){
                ansL=Info::op(ansL,node[l++]);
                L+=w;
            }
        }
        return L;
    }
    template<class F>
    int min_left(int R,F f){
        assert(0<=R&&R<=N);
        int r=N+R,w=1;
        value_type ansR=Info::e();
        for(;R-w>=0;r>>=1,w<<=1)if(r&1){
            if(!f(Info::op(node[r-1],ansR)))break;
            ansR=Info::op(node[--r],ansR);
            R-=w;
        }
        while(r<<=1,w>>=1){
            if(R-w>=0&&f(Info::op(node[r-1],ansR))){
                ansR=Info::op(node[r-1],ansR);
                R-=w;
                r--;
            }
        }
        return R;
    }
};