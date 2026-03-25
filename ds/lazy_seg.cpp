#pragma once
#include"../template.cpp"
#include"../other/commute_cheker.cpp"
template<class Info,class Tag>
struct lazy_segtree{
    using value_type=typename Info::value_type;
    using lazy_type=typename Tag::lazy_type;
    template<typename T,typename=void>
    struct has_leaf:false_type{};
    template<typename T>
    struct has_leaf<T,void_t<decltype(T::leaf())>>:true_type{};
    static constexpr value_type leaf(){
        if constexpr(has_leaf<Info>::value) {
            return Info::leaf();
        }else{
            return Info::e();
        }
    }
    int n;
    int lg;
    vc<value_type>node;
    vc<lazy_type>lazy;
    void build(int N){
        lg=0;
        while((1<<lg)<N)lg++;
        n=1<<lg;
        node=vc<value_type>(n*2,Info::e());
        lazy=vc<lazy_type>(n,Tag::id());
    }
    lazy_segtree(int N){
        build(N);
        if constexpr(has_leaf<Info>::value){
            REP(i,n,n*2)node[i]=leaf();
            DREP(i,n-1,1)update(i);
        }
    }
    lazy_segtree(int N,vc<value_type> A){
        build(N);
        A.resize(n,Info::e());
        REP(i,n,n*2)node[i]=A[i-n];
        DREP(i,n-1,1)update(i);
    }
    template<class F>
    lazy_segtree(int N,F f){
        build(N);
        REP(i,n,n*2){
            if(i-n<N)node[i]=f(i-n);
            else node[i]=Info::e();
        }
        DREP(i,n-1,1)update(i);
    }
    void all_apply(int k,lazy_type x){
        node[k]=Tag::Apply(node[k],x);
        if(k<n)lazy[k]=Tag::Merge(lazy[k],x);
    }
    void push(int k){
        all_apply(k*2,lazy[k]);
        all_apply(k*2+1,lazy[k]);
        lazy[k]=Tag::id();
    }
    void update(int i){
        node[i]=Info::op(node[i*2],node[i*2+1]);
    }
    void set(int i,value_type x){
        i+=n;
        for(int j=lg;j;j--)push(i>>j);
        node[i]=x;
        for(int j=1;j<=lg;j++)update(i>>j);
    }
    value_type prod(int l,int r){
        l+=n,r+=n;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        value_type sml=Info::e(),smr=Info::e();
        while(l<r){
            if(l&1)sml=Info::op(sml,node[l++]);
            if(r&1)smr=Info::op(node[--r],smr);
            l/=2,r/=2;
        }
        return Info::op(sml,smr);
    }
    void apply(int l,int r,lazy_type x){
        l+=n,r+=n;
        for(int i=lg;i;i--){
            if(((l>>i)<<i)!=l)push(l>>i);
            if(((r>>i)<<i)!=r)push((r-1)>>i);
        }
        int l2=l,r2=r;
        while(l2<r2){
            if(l2&1)all_apply(l2++,x);
            if(r2&1)all_apply(--r2,x);
            l2/=2,r2/=2;
        }
        for(int i=1;i<=lg;i++){
            if(((l>>i)<<i)!=l)update(l>>i);
            if(((r>>i)<<i)!=r)update((r-1)>>i);
        }
    }
    value_type all_prod(){
        return node[1];
    }
};