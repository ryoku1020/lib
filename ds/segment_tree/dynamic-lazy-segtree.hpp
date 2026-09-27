#pragma once
#include"../utility/node-pool.hpp"
template<class acted,class sztype=int>
struct dynamic_lazy_segtree{
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
    struct node{
        value_type val;
        lazy_type lazy;
        node*l,*r;
        node():val(info::id()),lazy(tag::id()),l(nullptr),r(nullptr){}
        node(value_type val):val(val),lazy(tag::id()),l(nullptr),r(nullptr){}
    };
    node_pool<node>pool;
    sztype N;
    int LOG;
    node*root;
    vc<value_type>db;
    node*new_node(const node&n){
        return pool.alloc(n);
    }
    node*make(node*x,int depth){
        if(!x->l){
            x->l=new_node({});
            x->r=new_node({});
            x->l->val=x->r->val=db[depth-1];
        }
        return x;
    }
    void eval(node*x,int depth){
        if(x->lazy==tag::id())return;
        x->l->lazy=tag::op(x->l->lazy,x->lazy);
        x->r->lazy=tag::op(x->r->lazy,x->lazy);
        x->l->val=acted::act(x->l->val,x->lazy,sztype(1)<<(depth-1));
        x->r->val=acted::act(x->r->val,x->lazy,sztype(1)<<(depth-1));
        x->lazy=tag::id();
    }
    value_type init_prod(sztype len){
        value_type res=info::id();
        for(int i=0;len;i++,len>>=1)if(len&1)res=info::op(res,db[i]);
        return res;
    }
    dynamic_lazy_segtree(sztype n,value_type leaf=info::id()){build(n,leaf);}
    void build(sztype n,value_type leaf=info::id()){
        assert(n>=0);
        LOG=1;
        while((i128(1)<<LOG)<n)LOG++;
        N=sztype(1)<<LOG;
        db.resize(LOG+1);
        db[0]=leaf;
        rep(i,LOG)db[i+1]=info::op(db[i],db[i]);
        root=new_node({});
        root->val=db.back();
    }
    void set(sztype i,value_type val){
        assert(0<=i&&i<N);
        auto dfs=[&](auto&dfs,sztype l,sztype r,node*root,int depth)->void{
            if(r-l==1){
                root->val=val;
                return;
            }
            make(root,depth);
            eval(root,depth);
            sztype mid=(l+r)>>1;
            if(l<=i&&i<mid)dfs(dfs,l,mid,root->l,depth-1);
            else dfs(dfs,mid,r,root->r,depth-1);
            root->val=info::op(root->l->val,root->r->val);
        };
        return dfs(dfs,0,N,root,LOG);
    }
    sztype common(sztype l1,sztype r1,sztype l2,sztype r2){
        return max(sztype(0),min(r1,r2)-max(l1,l2));
    }
    value_type prod(sztype l,sztype r){
        assert(0<=l&&l<=r&&r<=N);
        auto dfs=[&](auto&dfs,sztype sl,sztype sr,node*root,int depth,lazy_type x)->value_type{
            if(sr<=l)return info::id();
            if(r<=sl)return info::id();
            if(l<=sl&&sr<=r)return acted::act(root->val,x,sr-sl);
            sztype mid=(sl+sr)>>1;
            value_type res=info::id();
            x=tag::op(root->lazy,x);
            if(root->l)res=info::op(res,dfs(dfs,sl,mid,root->l,depth-1,x));
            else{
                sztype len=common(sl,mid,l,r);
                res=info::op(res,acted::act(init_prod(len),x,len));
            }
            if(root->r)res=info::op(res,dfs(dfs,mid,sr,root->r,depth-1,x));
            else{
                sztype len=common(mid,sr,l,r);
                res=info::op(res,acted::act(init_prod(len),x,len));
            }
            return res;
        };
        return dfs(dfs,0,N,root,LOG,tag::id());
    }
    void apply(sztype l,sztype r,lazy_type x){
        assert(0<=l&&l<=r&&r<=N);
        auto dfs=[&](auto&dfs,sztype sl,sztype sr,node*root,int depth)->void{
            if(sr<=l)return;
            if(r<=sl)return;
            if(l<=sl&&sr<=r){
                root->lazy=tag::op(root->lazy,x);
                root->val=acted::act(root->val,x,sr-sl);
                return;
            }
            make(root,depth);
            if constexpr(!commute)eval(root,depth);
            sztype mid=(sl+sr)>>1;
            dfs(dfs,sl,mid,root->l,depth-1);
            dfs(dfs,mid,sr,root->r,depth-1);
            root->val=acted::act(info::op(root->l->val,root->r->val),root->lazy,sr-sl);
        };
        return dfs(dfs,0,N,root,LOG);
    }
};