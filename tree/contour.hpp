#pragma once
#include"base.hpp"
#include"../ds/sequence/bit.hpp"
template<class T,class U=unweighted>
struct contour_add{
    tree<U>&tree;
    contour_add(::tree<U>&tree):tree(tree){}
    vc<binary_indexed_tree<T>>call_non;
    vc<T>cen1;
    vc<array<binary_indexed_tree<T>,2>>call_v;
    vc<T>cen2;
    vc<T>val;
    vvc<array<int,3>>appear;
    bool worked=false;
    void work(vc<ll>&first){
        val=first;
        appear=vvc<array<int,3>>(tree.size());
        if(!chmax(worked,1))return;
        auto callnon_f=[&](int cen,vvc<int>&g,vc<int>&is_virtual){
            int max_depth=0;
            {
                auto dfs=[&](auto&dfs,int u,int v,int d)->void{
                    chmax(max_depth,d);
                    for(auto&to:g[u]){
                        if(to==v)continue;
                        dfs(dfs,to,u,d+1);
                    }
                };
                dfs(dfs,cen,-1,0);
            }
            call_non.push_back(max_depth+1);
            auto dfs=[&](auto&dfs,int u,int v,int d)->void{
                {
                    if(!is_virtual[u])appear[u].pb({0,d,(int)call_non.size()-1});
                    if(!is_virtual[u])call_non.back().add(d,first[u]);
                }
                for(auto&to:g[u]){
                    if(to==v)continue;
                    dfs(dfs,to,u,d+1);
                }
            };
            dfs(dfs,cen,-1,0);
        };
        vc<int>depth(tree.size());
        auto callv_f=[&](int cen,vc<int>&col,vvc<int>&g,vc<int>&is_virtual){
            array<int,2>cd{};
            {
                auto dfs=[&](auto&dfs,int u,int v,int d)->void{
                    depth[u]=d;
                    chmax(cd[col[u]],d);
                    for(auto&to:g[u]){
                        if(to==v)continue;
                        dfs(dfs,to,u,d+1);
                    }
                };
                dfs(dfs,cen,-1,0);
            }
            call_v.push_back({cd[0]+1,cd[1]+1});
            auto dfs=[&](auto&dfs,int u,int v)->void{
                if(!is_virtual[u])appear[u].pb({col[u]+1,depth[u],(int)call_v.size()-1});
                if(!is_virtual[u]){
                    call_v.back()[col[u]].add(depth[u],first[u]);
                }
                for(auto&to:g[u]){
                    if(to!=v)dfs(dfs,to,u);
                }
            };dfs(dfs,cen,-1);
        };
        centroid_decomposition13(tree,callnon_f,callv_f);
    }
    T prod(int v,int r){
        assert(worked);
        assert(0<=r&&r<=tree.size());
        assert(0<=v&&v<tree.size());
        if(r==0)return 0;
        T ans=0;
        for(auto&[type,depth,idx]:appear[v]){
            if(type==0){
                if(depth==0&&min(r,call_non[idx].n)){
                    ans+=call_non[idx].sum(1,min(r,call_non[idx].n));
                }else{
                    if(depth<r){
                        ans+=call_non[idx].sum(0,1);
                    }
                }
            }
            if(type>=1){
                int col=type-1;
                if(r>=depth)ans+=call_v[idx][col^1].sum(0,min(r-depth,call_v[idx][col^1].n));
            }
        }
        return ans+val[v];
    }
    T prod(int v,int l,int r){
        assert(worked);
        assert(0<=l&&l<=r&&r<=tree.size());
        assert(0<=v&&v<tree.size());
        return prod(v,r)-prod(v,l);
    }
    void add(int v,T x){
        assert(worked);
        assert(0<=v&&v<tree.size());
        val[v]+=x;
        for(auto&[type,depth,idx]:appear[v]){
            if(type==0){
                call_non[idx].add(depth,x);
            }
            if(type>=1){
                int col=type-1;
                call_v[idx][col].add(depth,x);
            }
        }
    }
};
