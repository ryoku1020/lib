#pragma once
#include"../ds/utility/node-pool.hpp"
template<int sigma>
struct Trie{
    struct Node{
        array<Node*,sigma>cs;
        int cnt;
        Node():cs({}),cnt(0){}
    };
    node_pool<Node>nodes;
    Node*get_new(){
        return nodes.alloc();
    }
    Node*root;
    Trie(){
        root=get_new();
    }
    void insert(vc<int>v,int size){
        auto now=root;
        rep(i,v.size()){
            now->cnt+=size;
            if(now->cs[v[i]]==0)now->cs[v[i]]=get_new();
            now=now->cs[v[i]];
        }
        now->cnt+=size;
    }
    int size(){
        return root->cnt;
    }
};