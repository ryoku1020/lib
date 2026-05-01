#pragma once
#include "../template.hpp"
template<class Info,class sztype,bool is_persistent>
struct DynamicSegtree{
    using value_type=Info::value_type;
    struct Node{
        Node*l,*r;
        value_type val;
        Node():l(nullptr),r(nullptr),val(Info::e()){}
        Node(value_type x):l(nullptr),r(nullptr),val(x){}
    };
    int N,LOG;
    DynamicSegtree(int n){
        assert(n>=0);
        LOG=0;
        while((1<<LOG)<n)LOG++;
        N=1<<LOG;
    }
    Node*build(){return new Node(Info::get2(LOG));}
    value_type get(Node*x,int depth){return x?x->val:Info::get2(depth);}
    sztype common(sztype l1,sztype r1,sztype l2,sztype r2){return max(sztype(0),min(r1,r2)-max(l1,l2));}
    Node*set(Node*now,sztype i,value_type x){
        assert(now);
        assert(0<=i&&i<N);
        auto dfs=[&](auto&dfs,sztype l,sztype r,int depth,Node*cur)->Node*{
            Node*next=is_persistent?new Node(*cur):cur;
            if(r-l==1){next->val=x;return next;}
            sztype mid=(l+r)>>1;
            if(i<mid){
                if(!next->l)next->l=new Node(Info::get2(depth-1));
                next->l=dfs(dfs,l,mid,depth-1,next->l);
            }else{
                if(!next->r)next->r=new Node(Info::get2(depth-1));
                next->r=dfs(dfs,mid,r,depth-1,next->r);
            }
            next->val=Info::op(get(next->l,depth-1),get(next->r,depth-1));
            return next;
        };
        return dfs(dfs,0,N,LOG,now);
    }
    value_type prod(Node*now,int L,int R){
        assert(0<=L&&L<=R&&R<=N);
        auto dfs=[&](auto&dfs,int l,int r,int depth,Node*cur)->value_type{
            if(L<=l&&r<=R)return get(cur,depth);
            if(R<=l||r<=L)return Info::e();
            int mid=(l+r)>>1;
            Node*lc=cur?cur->l:nullptr,*rc=cur?cur->r:nullptr;
            if(!is_persistent&&cur){
                if(!lc)lc=cur->l=new Node(Info::get2(depth-1));
                if(!rc)rc=cur->r=new Node(Info::get2(depth-1));
            }
            return Info::op(dfs(dfs,l,mid,depth-1,lc),dfs(dfs,mid,r,depth-1,rc));
        };
        return dfs(dfs,0,N,LOG,now);
    }
};
