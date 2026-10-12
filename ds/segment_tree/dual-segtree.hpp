#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class info>
struct dual_segtree{
    using value_type=typename info::value_type;
    template<class T,class=void>
    struct has_commute{
        static constexpr bool value=false;
    };
    template<class T>
    struct has_commute<T,decltype((void)T::commute,void())>{
        static constexpr bool value=T::commute;
    };
    static constexpr bool commute=has_commute<info>::value;
    vc<value_type>lazy,node;
    int n,lg;
    dual_segtree(int N){
        assert(N>=0);
        lg=0;while((1<<lg)<N)lg++;
        n=1<<lg;
        lazy=vc<value_type>(n,info::id());
        node=vc<value_type>(n,info::id());
    }
    dual_segtree(int N,const vc<value_type>&v):dual_segtree(N){
        build(v);
    }
    void build(const vc<value_type>&v){
        assert((int)v.size()<=n);
        rep(i,v.size())node[i]=v[i];
    }
    void set(int p,value_type x,bool is_first=false){
        assert(0<=p&&p<n);
        if(!is_first){
            int k=p+n;
            for(int i=lg;i;i--)push(k>>i);
        }
        node[p]=x;
    }
    void all_apply(int k,value_type x){
        assert(0<=k&&k<n*2);
        if(k<n)lazy[k]=info::op(lazy[k],x);
        else node[k-n]=info::op(node[k-n],x);
    }
    void push(int k){
        assert(0<k&&k<n);
        all_apply(k*2,lazy[k]);
        all_apply(k*2+1,lazy[k]);
        lazy[k]=info::id();
    }
    void apply(int l,int r,value_type x){
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
            value_type res=info::id();
            for(int i=lg;i;i--)res=info::op(res,lazy[(p+n)>>i]);
            return info::op(node[p],res);
        }
        int k=p+n;
        for(int i=lg;i;i--)push(k>>i);
        return node[p];
    }
};
}
#ifdef LOCAL
#include"../../debug/formatters/ds--segment_tree--dual-segtree.hpp"
#endif