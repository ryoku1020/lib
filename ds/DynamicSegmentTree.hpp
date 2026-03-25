#pragma once
#include"../template.hpp"
template<class Info,class sztype=int>
struct DynamicSegmentTree{
    using value_type=typename Info::value_type;
    struct Node{
        int l,r;
        value_type val;
        Node():l(0),r(0),val(Info::e()){}
        Node(value_type x):l(0),r(0),val(x){}
    };
    int ptr=1;
    //N=10^9 Q=10^5
    static const int MAX_NODE=2e7;
    static Node inline pool[MAX_NODE];
    int new_node(const Node&n){
        pool[ptr]=n;
        return ptr++;
    }
    int root;
    vc<value_type>db;
    int N;
    int LOG;
    DynamicSegmentTree(int n){
        LOG=0;
        while((1<<LOG)<n)LOG++;
        N=1<<LOG;
        db.resize(LOG+1);
        db[0]=Info::leaf();
        rep(i,LOG)db[i+1]=Info::op(db[i],db[i]);
        root=new_node(db.back());
    }
    value_type get(int x,int depth){
        if(x)return pool[x].val;
        return db[depth];
    }
    sztype common(sztype l1,sztype r1,sztype l2,sztype r2){
        return max(sztype(0),min(r1,r2)-max(l1,l2));
    }
    void set(sztype i,value_type x){
        auto dfs=[&](auto&dfs,sztype l,sztype r,int depth,int now)->void{
            if(r-l==1){
                pool[now].val=x;
                return;
            }
            sztype mid=(l+r)>>1;
            if(l<=i&&i<mid){
                if(!pool[now].l)pool[now].l=new_node(db[depth-1]);
                dfs(dfs,l,mid,depth-1,pool[now].l);
            }else{
                if(!pool[now].r)pool[now].r=new_node(db[depth-1]);
                dfs(dfs,mid,r,depth-1,pool[now].r);
            }
            pool[now].val=Info::op(get(pool[now].l,depth-1),get(pool[now].r,depth-1));
        };
        dfs(dfs,0,N,LOG,root);
    }
    value_type prod(int L,int R){
        auto dfs=[&](auto&dfs,int l,int r,int depth,int now)->value_type{
            if(L<=l&&r<=R)return pool[now].val;
            if(R<=l||r<=L)return Info::e();
            int mid=(l+r)>>1;
            if(!pool[now].l)pool[now].l=new_node(db[depth-1]);
            if(!pool[now].r)pool[now].r=new_node(db[depth-1]);
            return Info::op(dfs(dfs,l,mid,depth-1,pool[now].l),dfs(dfs,mid,r,depth-1,pool[now].r));
        };
        return dfs(dfs,0,N,LOG,root);
    }
};