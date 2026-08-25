#pragma once
template<class info,class tag,class sztype=int>
struct dynamic_lazy_segtree{
    using value_type=typename info::value_type;
    using lazy_type=typename tag::lazy_type;
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
        int l,r;
        node():val(info::e()),lazy(tag::id()),l(0),r(0){}
        node(value_type val):val(val),lazy(tag::id()),l(0),r(0){}
    };
    //N=Q=10^5 > about 1.5e7
    static const int MAX_NODE=1.5e7;
    static node inline pool[MAX_NODE];
    int ptr=1;
    sztype N;
    int LOG;
    int root;
    vc<value_type>db;
    int new_node(const node&n){
        assert(ptr<MAX_NODE);
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
        if(pool[x].lazy==tag::id())return;
        pool[pool[x].l].lazy=tag::merge(pool[pool[x].l].lazy,pool[x].lazy);
        pool[pool[x].r].lazy=tag::merge(pool[pool[x].r].lazy,pool[x].lazy);
        pool[pool[x].l].val=tag::apply(pool[pool[x].l].val,pool[x].lazy);
        pool[pool[x].r].val=tag::apply(pool[pool[x].r].val,pool[x].lazy);
        pool[x].lazy=tag::id();
    }
    value_type init_prod(sztype len){
        value_type res=info::e();
        for(int i=0;len;i++,len>>=1)if(len&1)res=info::op(res,db[i]);
        return res;
    }
    dynamic_lazy_segtree(sztype n,value_type leaf=info::e()){build(n,leaf);}
    void build(sztype n,value_type leaf=info::e()){
        assert(n>=0);
        LOG=1;
        while((i128(1)<<LOG)<n)LOG++;
        N=sztype(1)<<LOG;
        db.resize(LOG+1);
        db[0]=leaf;
        rep(i,LOG)db[i+1]=info::op(db[i],db[i]);
        root=new_node({});
        pool[root].val=db.back();
    }
    void set(sztype i,value_type val){
        assert(0<=i&&i<N);
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
            pool[root].val=info::op(pool[pool[root].l].val,pool[pool[root].r].val);
        };
        return dfs(dfs,0,N,root,LOG);
    }
    sztype common(sztype l1,sztype r1,sztype l2,sztype r2){
        return max(sztype(0),min(r1,r2)-max(l1,l2));
    }
    value_type prod(sztype l,sztype r){
        assert(0<=l&&l<=r&&r<=N);
        auto dfs=[&](auto&dfs,sztype sl,sztype sr,int root,int depth,lazy_type x)->value_type{
            if(sr<=l)return info::e();
            if(r<=sl)return info::e();
            if(l<=sl&&sr<=r)return tag::apply(pool[root].val,x);
            sztype mid=(sl+sr)>>1;
            value_type res=info::e();
            x=tag::merge(pool[root].lazy,x);
            if(pool[root].l)res=info::op(res,dfs(dfs,sl,mid,pool[root].l,depth-1,x));
            else res=info::op(res,tag::apply(init_prod(common(sl,mid,l,r)),x));
            if(pool[root].r)res=info::op(res,dfs(dfs,mid,sr,pool[root].r,depth-1,x));
            else res=info::op(res,tag::apply(init_prod(common(mid,sr,l,r)),x));
            return res;
        };
        return dfs(dfs,0,N,root,LOG,tag::id());
    }
    void apply(sztype l,sztype r,lazy_type x){
        assert(0<=l&&l<=r&&r<=N);
        auto dfs=[&](auto&dfs,sztype sl,sztype sr,int root,int depth)->void{
            if(sr<=l)return;
            if(r<=sl)return;
            if(l<=sl&&sr<=r){
                pool[root].lazy=tag::merge(pool[root].lazy,x);
                pool[root].val=tag::apply(pool[root].val,x);
                return;
            }
            make(root,depth);
            if constexpr(!commute)eval(root);
            sztype mid=(sl+sr)>>1;
            dfs(dfs,sl,mid,pool[root].l,depth-1);
            dfs(dfs,mid,sr,pool[root].r,depth-1);
            pool[root].val=tag::apply(info::op(pool[pool[root].l].val,pool[pool[root].r].val),pool[root].lazy);
        };
        return dfs(dfs,0,N,root,LOG);
    }
};
