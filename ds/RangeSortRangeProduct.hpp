#pragma once
#include"fastset.hpp"
#include"segtree.hpp"
template<class Info,int D>
struct RangeSortRangeProduct{
    using V=Info::value_type;
    struct Node{
        Node*l,*r;
        int sum;
        V v,rv;
        Node():l(0),r(0),sum(0){
            v=rv=Info::e();
        }
        void update(){
            v=rv=Info::e();
            sum=0;
            if(l){
                v=l->v,rv=l->rv;
                sum+=l->sum;
            }
            if(r){
                v=Info::op(v,r->v);
                rv=Info::op(r->rv,rv);
                sum+=r->sum;
            }
        }
        
    };
    Node*Merge(Node*a,Node*b){
        if(!a)return b;
        if(!b)return a;
        a->l=Merge(a->l,b->l);
        a->r=Merge(a->r,b->r);
        delete b;
        a->update();
        return a;
    }
    pair<Node*,Node*>split(int k,Node*root){
        if(!root)return{nullptr,nullptr};
        if(k==0)return{nullptr,root};
        if(k==root->sum)return{root,nullptr};
        if(!root->l){
            auto res=split(k,root->r);
            Node*r1=new Node(),*r2=new Node();
            r1->r=res.first,r2->r=res.second;
            r1->update(),r2->update();
            delete root;
            return{r1,r2};
        }
        if(!root->r){
            auto res=split(k,root->l);
            Node*r1=new Node(),*r2=new Node();
            r1->l=res.first,r2->l=res.second;
            r1->update(),r2->update();
            delete root;
            return{r1,r2};
        }
        if(root->l->sum<=k){
            auto res=split(k-root->l->sum,root->r);
            Node*res_l=new Node();
            res_l->l=root->l,res_l->r=res.first;
            res_l->update();
            Node*res_r=new Node();
            res_r->r=res.second;
            res_r->update();
            delete root;
            return {res_l,res_r};
        }else{
            auto res=split(k,root->l);
            Node*res_r=new Node();
            res_r->l=res.second;res_r->r=root->r;
            res_r->update();
            Node*res_l=new Node();
            res_l->l=res.first;
            res_l->update();
            delete root;
            return {res_l,res_r};
        }
    }
    void make(Node*nnode,int p,int sz,V val){
        auto dfs=[&](auto&dfs,Node*target,int d){
            if(d<0){
                target->v=target->rv=val;
                target->sum=sz;
                return;
            }
            if(p>>d&1){
                target->r=new Node();
                dfs(dfs,target->r,d-1);
            }else{
                target->l=new Node();
                dfs(dfs,target->l,d-1);
            }
            target->update();
        };
        dfs(dfs,nnode,D-1);
    }
    int n;
    Segtree<Info>seg;
    FastSet fs;
    vc<Node*>tr;
    vc<int>flip;
    RangeSortRangeProduct(vc<int>p,vc<V>value):n(p.size()),seg(p.size()),fs(p.size()+1),tr(p.size()+1,nullptr),flip(p.size()+1,0){
        rep(i,n){
            tr[i]=new Node();
            make(tr[i],p[i],1,value[i]);
            seg.set(i,value[i]);
            fs.insert(i);
        }
        fs.insert(n);
    }
    void set(int i,Node*x,bool f){
        tr[i]=x;
        flip[i]=f;
        fs.insert(i);
        seg.set(i,(f?x->rv:x->v));
    }
    void erase(int i){
        seg.set(i,Info::e());
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
            auto nnode=Merge(tr[l],tr[j]);
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
        Node*nnode=new Node();
        make(nnode,p,1,x);
        set(i,nnode,false);
    }
};