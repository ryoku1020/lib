#pragma once
#include"../template.hpp"
#include"../math/StaticModInt.hpp"
using mint = StaticModInt<998244353>;
#include"../math/ModularArithmetic.hpp"

struct DisjointSetUnion{
    mint ans;
    vc<mint>w;
    vc<int>par;
    DisjointSetUnion(int n):par(n,-1),w(n),ans(0){}
    void set(int i,mint x){w[i]=x;}
    int root(int x){
        if(par[x]<0)return x;
        return par[x]=root(par[x]);
    }
    int same(int a,int b){
        return root(a)==root(b);
    }
    int merge(int a,int b){
        a=root(a),b=root(b);
        if(a==b)return 0;
        if(-par[a]<-par[b])swap(a,b);
        par[a]+=par[b];
        par[b]=a;
        ans+=w[a]*w[b];
        w[a]+=w[b];
        return 1;
    }
};
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