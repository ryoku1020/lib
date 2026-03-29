#pragma once
#include"noninfo.cpp"
template<class Info=Noninfo,class Tag=Nontag<Info>>
struct treap{
    using value_type=Info::value_type;
    using lazy_type=Tag::lazy_type;
    static uint32_t get_rand(){
        static uint32_t x=123456789,y=362436069,z=521288629,w=88675123;
        uint32_t t=x^(x<<11);x=y;y=z;z=w;
        return w=(w^(w>>19))^(t^(t>>8));
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
                    lc->sum=Tag::Apply(lc->sum,lazy);
                    lc->rev_sum=Tag::Apply(lc->rev_sum,lazy);
                    lc->lazy=Tag::Merge(lc->lazy,lazy);
                    lc->val=Tag::Apply(lc->val,lazy);
                    lc->has_lazy=1;
                }
                if(rc){
                    rc->sum=Tag::Apply(rc->sum,lazy);
                    rc->rev_sum=Tag::Apply(rc->rev_sum,lazy);
                    rc->lazy=Tag::Merge(rc->lazy,lazy);
                    rc->val=Tag::Apply(rc->val,lazy);
                    rc->has_lazy=1;
                }
                lazy=Tag::id();
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
            sum=Info::e();
            rev_sum=Info::e();
            size=1;
            if(lc){
                sum=Info::op(sum,lc->sum);
                rev_sum=Info::op(lc->rev_sum,rev_sum);
                size+=lc->size;
            }
            sum=Info::op(sum,val);
            rev_sum=Info::op(val,rev_sum);
            if(rc){
                sum=Info::op(sum,rc->sum);
                rev_sum=Info::op(rc->rev_sum,rev_sum);
                size+=rc->size;
            }
            return this;
        }
    };
    Node*pool;
    int pool_ptr;
    Node*root;
    treap(int max_nodes=1000005){
        pool=(Node*)malloc(sizeof(Node)*max_nodes);
        pool_ptr=0;
        root=NULL;
    }
    Node*new_node(){
        Node*res=&pool[pool_ptr++];
        res->lc=res->rc=0;
        res->val=res->sum=res->rev_sum=Info::e();
        res->lazy=Tag::id();
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
        auto sp=split(x,k);
        auto ins=new_node();ins->val=v;ins->sum=ins->rev_sum=v;
        return merge(sp.first,merge(ins,sp.second));
    }
    Node*erase(Node*x,int k){
        auto s1=split(x,k);
        auto s2=split(s1.second,1);
        return merge(s1.first,s2.second);
    }
    Node*apply(Node*x,lazy_type v,int l,int r){
        if(l==r)return x;
        auto s1=split(x,l);
        auto s2=split(s1.second,r-l);
        s2.first->lazy=Tag::Merge(s2.first->lazy,v);
        s2.first->val=Tag::Apply(s2.first->val,v);
        s2.first->sum=Tag::Apply(s2.first->sum,v);
        s2.first->rev_sum=Tag::Apply(s2.first->rev_sum,v);
        s2.first->has_lazy=1;
        return merge(s1.first,merge(s2.first,s2.second));
    }
    pair<Node*,value_type>prod(Node*x,int l,int r){
        if(l==r)return {x,Info::e()};
        auto s1=split(x,l);
        auto s2=split(s1.second,r-l);
        auto res=s2.first->sum;
        return {merge(s1.first,merge(s2.first,s2.second)),res};
    }
    Node*reverse(Node*x,int l,int r){
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