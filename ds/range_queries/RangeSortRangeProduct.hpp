#pragma once
#include"../ordered/fastset.hpp"
#include"../segment_tree/segtree.hpp"
template<class info,int D>
struct range_sort_range_product{
    using V=info::value_type;
    struct node{
        node*l,*r;
        int sum;
        V v,rv;
        node():l(0),r(0),sum(0){
            v=rv=info::e();
        }
        void update(){
            v=rv=info::e();
            sum=0;
            if(l){
                v=l->v,rv=l->rv;
                sum+=l->sum;
            }
            if(r){
                v=info::op(v,r->v);
                rv=info::op(r->rv,rv);
                sum+=r->sum;
            }
        }
        
    };
    node*merge(node*a,node*b){
        if(!a)return b;
        if(!b)return a;
        a->l=merge(a->l,b->l);
        a->r=merge(a->r,b->r);
        delete b;
        a->update();
        return a;
    }
    pair<node*,node*>split(int k,node*root){
        if(!root)return{nullptr,nullptr};
        if(k==0)return{nullptr,root};
        if(k==root->sum)return{root,nullptr};
        if(!root->l){
            auto res=split(k,root->r);
            node*r1=new node(),*r2=new node();
            r1->r=res.first,r2->r=res.second;
            r1->update(),r2->update();
            delete root;
            return{r1,r2};
        }
        if(!root->r){
            auto res=split(k,root->l);
            node*r1=new node(),*r2=new node();
            r1->l=res.first,r2->l=res.second;
            r1->update(),r2->update();
            delete root;
            return{r1,r2};
        }
        if(root->l->sum<=k){
            auto res=split(k-root->l->sum,root->r);
            node*res_l=new node();
            res_l->l=root->l,res_l->r=res.first;
            res_l->update();
            node*res_r=new node();
            res_r->r=res.second;
            res_r->update();
            delete root;
            return {res_l,res_r};
        }else{
            auto res=split(k,root->l);
            node*res_r=new node();
            res_r->l=res.second;res_r->r=root->r;
            res_r->update();
            node*res_l=new node();
            res_l->l=res.first;
            res_l->update();
            delete root;
            return {res_l,res_r};
        }
    }
    void make(node*nnode,int p,int sz,V val){
        auto dfs=[&](auto&dfs,node*target,int d){
            if(d<0){
                target->v=target->rv=val;
                target->sum=sz;
                return;
            }
            if(p>>d&1){
                target->r=new node();
                dfs(dfs,target->r,d-1);
            }else{
                target->l=new node();
                dfs(dfs,target->l,d-1);
            }
            target->update();
        };
        dfs(dfs,nnode,D-1);
    }
    int n;
    segtree<info>seg;
    fast_set fs;
    vc<node*>tr;
    vc<int>flip;
    range_sort_range_product(vc<int>p,vc<V>value):n(p.size()),seg(p.size()),fs(p.size()+1),tr(p.size()+1,nullptr),flip(p.size()+1,0){
        rep(i,n){
            tr[i]=new node();
            make(tr[i],p[i],1,value[i]);
            seg.set(i,value[i]);
            fs.insert(i);
        }
        fs.insert(n);
    }
    void set(int i,node*x,bool f){
        tr[i]=x;
        flip[i]=f;
        fs.insert(i);
        seg.set(i,(f?x->rv:x->v));
    }
    void erase(int i){
        seg.set(i,info::e());
        fs.erase(i);
        tr[i]=nullptr;
        flip[i]=0;
    }
    void MMSplit(int x){
        if(x==n)return;
        if(fs.count(x))return;
        assert(x>=0);
        int l=fs.prev(x);
        auto nnode=tr[l];
        bool f=flip[l];
        if(!f){
            auto [sl,sr]=split(x-l,nnode);
            set(l,sl,false),set(x,sr,false);
        }else{
            auto [sr,sl]=split(nnode->sum-(x-l),nnode);
            set(l,sl,true);
            set(x,sr,true);
        }
    }
    void modify(int l,int r){
        MMSplit(l);
        MMSplit(r);
    }
    //[l,r)
    void sort(int l,int r){
        if(l==r)return;
        modify(l,r);
        while(1){
            int j=fs.next(l+1);
            if(j==r)break;
            auto nnode=merge(tr[l],tr[j]);
            erase(j);
            set(l,nnode,false);
        }
        set(l,tr[l],false);
    }
    void rsort(int l,int r){
        if(l==r)return;
        sort(l,r);
        set(l,tr[l],1);
    }
    V prod(int l,int r){
        modify(l,r);
        return seg.prod(l,r);
    }
    void set(int i,int p,V x){
        modify(i,i+1);
        node*nnode=new node();
        make(nnode,p,1,x);
        set(i,nnode,false);
    }
};
