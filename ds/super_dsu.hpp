#pragma once 
#include "../template.hpp"
#include "uf.hpp"

struct SuperDisjointSetUnion{
    int n;
    int lg;
    vc<DisjointSetUnion>ds;
    SuperDisjointSetUnion(int n):n(n){
        lg=1;
        while((1<<lg)<=n)lg++;
        ds=vc<DisjointSetUnion>(lg,1);
        rep(i,lg){
            ds[i]=DisjointSetUnion(n-(1<<i)+1);
        }
    }
    int root(int x){
        return ds[0].root(x);
    }
    void merge(int l,int r,int L){
        if(l==r)return;
        if(l>r)swap(l,r);
        if(L==0)return;
        auto dfs=[&](auto&dfs,int depth,int tl,int tr,int sl,int sr)->void{
            if(ds[depth].same(tl,sl))return;
            ds[depth].merge(tl,sl);
            if(depth==0)return;
            int LEN=(tr-tl);
            dfs(dfs,depth-1,tl,tl+LEN/2,sl,sl+LEN/2);
            dfs(dfs,depth-1,tr-LEN/2,tr,sr-LEN/2,sr);
        };
        int LOG=0;while((1<<(LOG+1))<=L)LOG++;
        dfs(dfs,LOG,l,l+(1<<LOG),r,r+(1<<LOG));
        dfs(dfs,LOG,l+L-(1<<LOG),l+L,r+L-(1<<LOG),r+L);
    }
};