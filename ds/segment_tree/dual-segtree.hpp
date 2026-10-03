#pragma once
template<class acted>
struct dual_segtree{
    using info=typename acted::info;
    using tag=typename acted::tag;
    using value_type=typename acted::value_type;
    using lazy_type=typename acted::lazy_type;
    template<class T,class=void>
    struct has_commute{
        static constexpr bool value=false;
    };
    template<class T>
    struct has_commute<T,decltype((void)T::commute,void())>{
        static constexpr bool value=T::commute;
    };
    static constexpr bool commute=has_commute<tag>::value;
    vc<lazy_type>lazy;
    vc<value_type>node;
    int n;
    int lg;
    dual_segtree(int N){
        assert(N>=0);
        lg=0;while((1<<lg)<N)lg++;
        n=1<<lg;
        lazy=vc<lazy_type>(n,tag::id());
        node=vc<value_type>(n,info::id());
    }
    dual_segtree(int N,const vc<value_type>&v){
        assert(N>=0);
        lg=0;while((1<<lg)<N)lg++;
        n=1<<lg;
        lazy=vc<lazy_type>(n,tag::id());
        node=vc<value_type>(n,info::id());
        build(v);
    }
    void build(const vc<value_type>&v){
        assert((int)v.size()<=n);
        rep(i,v.size())node[i]=v[i];
    }
    void set(int p,value_type x,bool is_first=false){
        assert(0<=p&&p<n);
        if(is_first==0){
            int k=p+n;
            for(int i=lg;i;i--)push(k>>i);
        }
        node[p]=x;
    }
    void all_apply(int k,lazy_type x){
        assert(0<=k&&k<n*2);
        if(k<n)lazy[k]=tag::op(lazy[k],x);
        else node[k-n]=acted::act(node[k-n],x,1);
    }
    void push(int k){
        assert(0<k&&k<n);
        all_apply(k*2,lazy[k]);
        all_apply(k*2+1,lazy[k]);
        lazy[k]=tag::id();
    }
    void apply(int l,int r,lazy_type x){
        assert(0<=l&&l<=r&&r<=n);
        if(l==r)return;
        l+=n,r+=n;
        if constexpr(!commute){
            for(int i=lg;i;i--){
                if(((l>>i)<<i)!=l)push(l>>i);
                if(((r>>i)<<i)!=r)push((r-1)>>i);
            }
        }
        while(l<r){
            if(l&1)all_apply(l++,x);
            if(r&1)all_apply(--r,x);
            l/=2,r/=2;
        }
    }
    value_type get(int p){
        assert(0<=p&&p<n);
        if constexpr(commute){
            lazy_type res=tag::id();
            for(int i=lg;i;i--)res=tag::op(res,lazy[(p+n)>>i]);
            return acted::act(node[p],res,1);
        }
        int k=p+n;
        for(int i=lg;i;i--)push(k>>i);
        return node[p];
    }
};