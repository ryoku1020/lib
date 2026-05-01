#pragma once
#include"../template.hpp"
template<int sigma>
struct EerTree{
    vc<array<int,sigma>>child;
    vc<int>suffix;
    vc<int>suffix_tree_depth;
    vc<int>len;
    vc<int>in;
    vc<int>pali_node;

    int now_node;
    vc<int>S;
    
    int new_node(){
        static int id=0;
        child.push_back({});rep(i,sigma)child.back()[i]=-1e9;
        suffix.push_back(-1e9);
        suffix_tree_depth.push_back(-1e9);
        len.push_back(-1e9);
        in.push_back(-1e9);
        return id++;
    }
    void add(int i){
        while(1){
            if(i-len[now_node]-1>=0&&S[i]==S[i-len[now_node]-1]){
                auto nxt_suffix_node=suffix[now_node];

                while(nxt_suffix_node){
                    auto&target=child[nxt_suffix_node][S[i]];
                    if(target>=0&&i-len[nxt_suffix_node]-1>=0&&S[i-len[nxt_suffix_node]-1]==S[i])break;
                    nxt_suffix_node=suffix[nxt_suffix_node];
                }

                if(child[nxt_suffix_node][S[i]]>=0){
                    nxt_suffix_node=child[nxt_suffix_node][S[i]];
                }else nxt_suffix_node=1;

                if(child[now_node][S[i]]>=0){
                    now_node=child[now_node][S[i]];
                    pali_node.push_back(now_node);
                    return;
                }
                int nxt_node=new_node();

                child[now_node][S[i]]=nxt_node;
                suffix[nxt_node]=nxt_suffix_node;
                suffix_tree_depth[nxt_node]=suffix_tree_depth[nxt_suffix_node]+1;
                len[nxt_node]=len[now_node]+2;
                now_node=nxt_node;

                pali_node.push_back(now_node);
                return;
            }else{
                now_node=suffix[now_node];
            }
        }
    }
    void build(string s,char CHRMIN){
        S.resize(s.size());
        rep(i,s.size()){
            S[i]=s[i]-CHRMIN;
            assert(0<=S[i]&&S[i]<sigma);
        }

        new_node();
        suffix.back()=0;
        suffix_tree_depth.back()=0;
        len.back()=-1;

        now_node=new_node();
        suffix.back()=0;
        suffix_tree_depth.back()=1;
        len.back()=0;

        rep(i,s.size())add(i);
    }
};
