#pragma once
#include"../utility/noninfo.hpp"
#include <random>
template<class info=noninfo,class tag=nontag<info>>
struct treap{
    using value_type=info::value_type;
    using lazy_type=tag::lazy_type;
    mt19937 mt;
    uint32_t get_rand(){
        return mt();
    }
    struct Node{
        Node*lc,*rc;
        value_type val,sum,rev_sum;
        lazy_type lazy;
        int size;
        uint32_t pri;
        bool rev,has_lazy;
        void push(){
            if(has_lazy){
                if(lc){
                    lc->sum=tag::apply(lc->sum,lazy);
                    lc->rev_sum=tag::apply(lc->rev_sum,lazy);
                    lc->lazy=tag::merge(lc->lazy,lazy);
                    lc->val=tag::apply(lc->val,lazy);
                    lc->has_lazy=1;
                }
                if(rc){
                    rc->sum=tag::apply(rc->sum,lazy);
                    rc->rev_sum=tag::apply(rc->rev_sum,lazy);
                    rc->lazy=tag::merge(rc->lazy,lazy);
                    rc->val=tag::apply(rc->val,lazy);
                    rc->has_lazy=1;
                }
                lazy=tag::id();
                has_lazy=0;
            }
            if(rev){
                swap(lc,rc);
                if(lc){
                    lc->rev^=1;
                    swap(lc->sum,lc->rev_sum);
                }
                if(rc){
                    rc->rev^=1;
                    swap(rc->sum,rc->rev_sum);
                }
                rev=0;
            }
        }
        Node*update(){
            sum=info::e();
            rev_sum=info::e();
            size=1;
            if(lc){
                sum=info::op(sum,lc->sum);
                rev_sum=info::op(lc->rev_sum,rev_sum);
                size+=lc->size;
            }
            sum=info::op(sum,val);
            rev_sum=info::op(val,rev_sum);
            if(rc){
                sum=info::op(sum,rc->sum);
                rev_sum=info::op(rc->rev_sum,rev_sum);
                size+=rc->size;
            }
            return this;
        }
    };
    Node*pool;
    int pool_ptr;
    int max_nodes;
    Node*root;
    treap(int max_nodes):max_nodes(max_nodes){
        mt.seed(random_device{}());
        assert(max_nodes>0);
        pool=(Node*)malloc(sizeof(Node)*max_nodes);
        pool_ptr=0;
        root=NULL;
    }
    Node*new_node(){
        assert(pool);
        assert(pool_ptr<max_nodes);
        Node*res=&pool[pool_ptr++];
        res->lc=res->rc=0;
        res->val=res->sum=res->rev_sum=info::e();
        res->lazy=tag::id();
        res->size=1;
        res->pri=get_rand();
        res->rev=res->has_lazy=0;
        return res;
    }
    Node*build(int l,int r,const vc<value_type>&v){
        if(l==r)return NULL;
        int mid=l+(r-l)/2;
        Node*res=new_node();
        res->val=v[mid];
        res->lc=build(l,mid,v);
        res->rc=build(mid+1,r,v);
        return res->update();
    }
    void build(const vc<value_type>&v){
        assert(pool_ptr+v.size()<=max_nodes);
        root=build(0,v.size(),v);
    }
    Node*merge(Node*l,Node*r){
        if(!l)return r;
        if(!r)return l;
        if(l->pri>r->pri){
            l->push();
            l->rc=merge(l->rc,r);
            return l->update();
        }else{
            r->push();
            r->lc=merge(l,r->lc);
            return r->update();
        }
    }
    pair<Node*,Node*>split(Node*l,int k){
        if(!l)return {NULL,NULL};
        if(k==0)return {NULL,l};
        l->push();
        int lsz=l->lc?l->lc->size:0;
        if(lsz>=k){
            auto res=split(l->lc,k);
            l->lc=res.second;
            return {res.first,l->update()};
        }else{
            auto res=split(l->rc,k-lsz-1);
            l->rc=res.first;
            return {l->update(),res.second};
        }
    }
    Node*insert(Node*x,int k,value_type v){
        int sz=x?x->size:0;
        assert(0<=k&&k<=sz);
        auto sp=split(x,k);
        auto ins=new_node();ins->val=v;ins->sum=ins->rev_sum=v;
        return merge(sp.first,merge(ins,sp.second));
    }
    Node*erase(Node*x,int k){
        assert(x);
        assert(0<=k&&k<x->size);
        auto s1=split(x,k);
        auto s2=split(s1.second,1);
        return merge(s1.first,s2.second);
    }
    Node*apply(Node*x,lazy_type v,int l,int r){
        int sz=x?x->size:0;
        assert(0<=l&&l<=r&&r<=sz);
        if(l==r)return x;
        auto s1=split(x,l);
        auto s2=split(s1.second,r-l);
        s2.first->lazy=tag::merge(s2.first->lazy,v);
        s2.first->val=tag::apply(s2.first->val,v);
        s2.first->sum=tag::apply(s2.first->sum,v);
        s2.first->rev_sum=tag::apply(s2.first->rev_sum,v);
        s2.first->has_lazy=1;
        return merge(s1.first,merge(s2.first,s2.second));
    }
    pair<Node*,value_type>prod(Node*x,int l,int r){
        int sz=x?x->size:0;
        assert(0<=l&&l<=r&&r<=sz);
        if(l==r)return {x,info::e()};
        auto s1=split(x,l);
        auto s2=split(s1.second,r-l);
        auto res=s2.first->sum;
        return {merge(s1.first,merge(s2.first,s2.second)),res};
    }
    Node*reverse(Node*x,int l,int r){
        int sz=x?x->size:0;
        assert(0<=l&&l<=r&&r<=sz);
        if(l==r)return x;
        auto s1=split(x,l);
        auto s2=split(s1.second,r-l);
        s2.first->rev^=1;
        swap(s2.first->sum,s2.first->rev_sum);
        return merge(s1.first,merge(s2.first,s2.second));
    }
    void insert(int k,value_type v){root=insert(root,k,v);}
    void erase(int k){root=erase(root,k);}
    void apply(int l,int r,lazy_type x){root=apply(root,x,l,r);}
    void reverse(int l,int r){root=reverse(root,l,r);}
    value_type prod(int l,int r){
        auto res=prod(root,l,r);
        root=res.first;

        return res.second;
    }
    
};
