#pragma once
#include"../template.cpp"
template<class Info,class Tag,class sztype=int>
struct dynamic_lazysegtree{
    using value_type=typename Info::value_type;
    using lazy_type=typename Tag::lazy_type;
    struct Node{
        value_type val;
        lazy_type lazy;
        int l,r;
        Node():val(Info::e()),lazy(Tag::id()),l(0),r(0){}
        Node(value_type val):val(val),lazy(Tag::id()),l(0),r(0){}
    };
    //N=Q=10^5 > about 1.5e7
    static const int MAX_NODE=1.5e7;
    static Node inline pool[MAX_NODE];
    int ptr=1;
    sztype N;
    int LOG;
    int root;
    vc<value_type>db;
    int new_node(const Node&n){
        pool[ptr]=n;
        return ptr++;
    }
    int make(int x,int depth){
        if(!pool[x].l){
            pool[x].l=new_node({});
            pool[x].r=new_node({});
            pool[pool[x].l].val=pool[pool[x].r].val=db[depth-1];
        }
        return x;
    }
    void eval(int x){
        if(pool[x].lazy==Tag::id())return;
        pool[pool[x].l].lazy=Tag::Merge(pool[pool[x].l].lazy,pool[x].lazy);
        pool[pool[x].r].lazy=Tag::Merge(pool[pool[x].r].lazy,pool[x].lazy);
        pool[pool[x].l].val=Tag::Apply(pool[pool[x].l].val,pool[x].lazy);
        pool[pool[x].r].val=Tag::Apply(pool[pool[x].r].val,pool[x].lazy);
        pool[x].lazy=Tag::id();
    }
    dynamic_lazysegtree(sztype n){build(n);}
    void build(sztype n){
        LOG=1;
        while((i128(1)<<LOG)<n)LOG++;
        N=sztype(1)<<LOG;
        db.resize(LOG+1);
        db[0]=Info::leaf();
        rep(i,LOG)db[i+1]=Info::op(db[i],db[i]);
        root=new_node({});
        pool[root].val=db.back();
    }
    void set(sztype i,value_type val){
        auto dfs=[&](auto&dfs,sztype l,sztype r,int root,int depth)->void{
            if(r-l==1){
                pool[root].val=val;
                return;
            }
            make(root,depth);
            eval(root);
            sztype mid=(l+r)>>1;
            if(l<=i&&i<mid)dfs(dfs,l,mid,pool[root].l,depth-1);
            else dfs(dfs,mid,r,pool[root].r,depth-1);
            pool[root].val=Info::op(pool[pool[root].l].val,pool[pool[root].r].val);
        };
        return dfs(dfs,0,N,root,LOG);
    }
    sztype common(sztype l1,sztype r1,sztype l2,sztype r2){
        return max(sztype(0),min(r1,r2)-max(l1,l2));
    }
    value_type prod(sztype l,sztype r){
        auto dfs=[&](auto&dfs,sztype sl,sztype sr,int root,int depth,lazy_type x)->value_type{
            if(sr<=l)return Info::e();
            if(r<=sl)return Info::e();
            if(l<=sl&&sr<=r)return Tag::Apply(pool[root].val,x);
            sztype mid=(sl+sr)>>1;
            value_type res=Info::e();
            x=Tag::Merge(pool[root].lazy,x);
            if(pool[root].l)res=Info::op(res,dfs(dfs,sl,mid,pool[root].l,depth-1,x));
            else res=Info::op(res,Tag::Apply(Info::bylen(common(sl,mid,l,r),db),x));
            if(pool[root].r)res=Info::op(res,dfs(dfs,mid,sr,pool[root].r,depth-1,x));
            else res=Info::op(res,Tag::Apply(Info::bylen(common(mid,sr,l,r),db),x));
            return res;
        };
        return dfs(dfs,0,N,root,LOG,Tag::id());
    }
    void apply(sztype l,sztype r,lazy_type x){
        auto dfs=[&](auto&dfs,sztype sl,sztype sr,int root,int depth)->void{
            if(sr<=l)return;
            if(r<=sl)return;
            if(l<=sl&&sr<=r){
                pool[root].lazy=Tag::Merge(pool[root].lazy,x);
                pool[root].val=Tag::Apply(pool[root].val,x);
                return;
            }
            make(root,depth);
            eval(root);
            sztype mid=(sl+sr)>>1;
            dfs(dfs,sl,mid,pool[root].l,depth-1);
            dfs(dfs,mid,sr,pool[root].r,depth-1);
            pool[root].val = Info::op(pool[pool[root].l].val, pool[pool[root].r].val);
        };
        return dfs(dfs,0,N,root,LOG);
    }
};