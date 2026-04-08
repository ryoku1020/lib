#pragma once
#include"../template.hpp"
struct BinaryTrie{
    struct Node{
        Node*l,*r;
        int size;
        Node():l(nullptr),r(nullptr),size(0){}
    };
    int all_size;
    T offset;
    Node*root;
    BinaryTrie(){
        root=new Node();
    }
    void insert(T val,int x=1){
        assert(val>=0);
        auto dfs=[&](auto&dfs,Node*now,T l,T r,int target)->void{
            if(r-l==1){
                now->size+=x;
            }
            T mid=(l+r)>>1;
            if((val<mid)^(offset>>target&1)){
                if(now->l==0)now->l=new Node();
                dfs(dfs,now->l,l,mid,target-1);
            }else{
                if(now->r==0)now->r=new Node();
                dfs(dfs,now->r,mid,r,target-1);
            }
            now->size+=x;
        };
        dfs(dfs,root,0,T(1)<<depth,depth-1);
        all_size+=x;
    }
    void all_xor(T x){
        offset^=x;
    }
    T find_min(){
        assert(all_size);
        auto dfs=[&](auto&dfs,Node*now,T l,T r,int target)->T{
            if(r-l==1){
                return l;
            }
            T mid=(l+r)>>1;
            if(!(offset>>target&1)&&now->l&&now->l->size){
                return dfs(dfs,now->l,l,mid,target-1);
            }else{
                return dfs(dfs,now->r,mid,r,target-1);
            }
        };
        dfs(dfs,root,0,T(1)<<depth,depth-1);
    }
    
};