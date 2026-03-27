#pragma  once
#include "../template.hpp"
template<class X>
struct DualSegmentTree{
    using value_type=X::value_type;
    vc<value_type>lazy;
    vc<value_type>node;
    int n;
    int lg;
    DualSegmentTree(int N){
        lg=0;while((1<<lg)<N)lg++;
        n=1<<lg;
        lazy=vc<value_type>(n,X::e());
        node=vc<value_type>(n*2,X::e());
    }
    DualSegmentTree(int N,const vc<value_type>&v){
        lg=0;while((1<<lg)<N)lg++;
        n=1<<lg;
        lazy=vc<value_type>(n,X::e());
        node=vc<value_type>(n*2,X::e());
        build(v);
    }
    void build(const vc<value_type>&v){
        rep(i,n)node[i+n]=v[i];
    }
    void set(int p,value_type x,bool is_first=false){
        if(is_first==0){
            p+=n;
            for(int i=lg;i;i--)push(p>>i);
            node[p]=x;
        }else node[p+n]=x;
    }
    void all_apply(int k,value_type x){
        node[k]=X::op(node[k],x);
        if(k<n)lazy[k]=X::op(lazy[k],x);
    }
    void push(int k){
        all_apply(k*2,lazy[k]);
        all_apply(k*2+1,lazy[k]);
        lazy[k]=X::e();
    }
    void apply(int l,int r,value_type x){
        l+=n,r+=n;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        while(l<r){
            if(l&1)all_apply(l++,x);
            if(r&1)all_apply(--r,x);
            l/=2,r/=2;
        }
    }
    value_type get(int p){
        p+=n;
        for(int i=lg;i;i--)push(p>>i);
        return node[p];
    }
};