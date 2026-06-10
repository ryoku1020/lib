#pragma once
#include <random>
template<class T>
struct SetTreap{
    struct Node{
        Node*lc,*rc;
        T val;
        int pri;
        int size;
        Node*update(){
            size=1;
            if(lc)size+=lc->size;
            if(rc)size+=rc->size;
            return this;
        }
    };
    void build(vc<T>v){
        for(auto&x:v)assert(x>=0);
        sort(all(v));
        v.erase(unique(all(v)),v.end());
        int n=v.size();
        if(n==0){
            root=NULL;
            return;
        }
        vc<Node*>pts(n);
        for(int i=0;i<n;i++){
            pts[i]=new_node();
            pts[i]->val=v[i];
            pts[i]->pri=mt();
        }
        vc<Node*>st;
        for(int i=0;i<n;i++){
            Node*last=NULL;
            while(!st.empty()&&st.back()->pri<pts[i]->pri){
                last=st.back();
                st.pop_back();
            }
            pts[i]->lc=last;
            if(!st.empty())st.back()->rc=pts[i];
            st.push_back(pts[i]);
        }
        root=st[0];
        auto dfs=[&](auto&self,Node*cur)->void{
            if(!cur)return;
            self(self,cur->lc);
            self(self,cur->rc);
            cur->update();
        };
        dfs(dfs,root);
    }
    Node*new_node(){
        Node*nn=new Node();
        nn->pri=mt();
        nn->lc=nn->rc=0;
        nn->size=1;
        return nn;
    }
    static mt19937 mt;
    Node*root;
    SetTreap(){
        root=NULL;
    }
    Node*merge(Node*l,Node*r){
        if(!l)return r;
        if(!r)return l;
        if(l->pri>r->pri){
            l->rc=merge(l->rc,r);
            return l->update();
        }else{
            r->lc=merge(l,r->lc);
            return r->update();
        }
    }
    pair<Node*,Node*>split(Node*l,T k){
        if(!l)return {NULL,NULL};
        if(l->val<k){
            auto res=split(l->rc,k);
            l->rc=res.first;
            return {l->update(),res.second};
        }else{
            auto res=split(l->lc,k);
            l->lc=res.second;
            return {res.first,l->update()};
        }
    }
    Node*insert(Node*x,T val){
        auto s1=split(x,val);
        auto s2=split(s1.second,val+1);
        if(s2.first==NULL){
            s2.first=new_node();
            s2.first->val=val;
        }
        return merge(s1.first,merge(s2.first,s2.second));
    }
    void insert(T val){
        assert(val>=0);
        root=insert(root,val);
    }
    Node*erase(Node*x,T val){
        auto s1=split(x,val);
        auto s2=split(s1.second,val+1);
        return merge(s1.first,s2.second);
    }
    void erase(T val){
        assert(val>=0);
        root=erase(root,val);
    }
    bool count(T val){
        assert(val>=0);
        auto s1=split(root,val);
        auto s2=split(s1.second,val+1);
        auto res=s2.first!=NULL;
        root=merge(s1.first,merge(s2.first,s2.second));
        return res;
    }
    //min in [val,♾️)
    T next(T val){
        assert(val>=0);
        auto s1=split(root,val);
        auto now=s1.second;
        while(now){
            if(now->lc==NULL)break;
            now=now->lc;
        }
        T ans=numeric_limits<T>::max();
        if(now)chmin(ans,now->val);
        root=merge(s1.first,s1.second);
        if(ans==numeric_limits<T>::max())return -1;
        else return ans;
    }
    //max in (-♾️,val)
    T prev(T val){
        assert(val>=0);
        auto s1=split(root,val);
        auto now=s1.first;
        while(now){
            if(now->rc==NULL)break;
            now=now->rc;
        }
        T ans=-1;
        if(now)chmax(ans,now->val);
        root=merge(s1.first,s1.second);
        return ans;
    }
    //[val,♾️)
    int bigger(T val){
        assert(val>=0);
        int ans=size();
        auto s1=split(root,val);
        if(s1.first)ans-=s1.first->size;
        root=merge(s1.first,s1.second);
        return ans;
    }
    int size(){
        if(root==NULL)return 0;
        return root->size;
    }
    //(-♾️,val)
    int smaller(T val){
        assert(val>=0);
        if(root==NULL)return 0;
        return size()-bigger(val);
    }
    //[l,r)
    int range_count(T l,T r){
        assert(0<=l&&l<=r);
        return -bigger(r)+bigger(l);
    }
    T kth(Node*x,int k){
        assert(x);
        assert(0<=k&&k<x->size);
        if(x->lc){
            if(x->lc->size>k){
                return kth(x->lc,k);
            }
            k-=x->lc->size;
        }
        if(k==0)return x->val;
        --k;
        return kth(x->rc,k);
    }
    T kth(int k){
        assert(k>=0);
        if(k>=size())return -1;
        return kth(root,k);
    }
};
template<class T>
mt19937 SetTreap<T>::mt(random_device{}());
