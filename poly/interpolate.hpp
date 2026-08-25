#pragma once
#include"base.hpp"
#include"multipoint-evaluation.hpp"
template<class mint>
fps<mint>interpolate(vc<mint>x,vc<mint>y){
    assert(mint::get_mod());
    assert(x.size()==y.size());
    int n=x.size();
    int sz=1;
    while(sz<n)sz*=2;
    vc<fps<mint>>tree(sz*2,{1});
    rep(i,n)tree[sz+i]=fps<mint>{-x[i],1};
    DREP(i,sz-1,1)tree[i]=tree[i*2]*tree[i*2+1];
    auto gdeval=multipoint_evaluation(tree[1].diff(),x);
    vc<mint>a(n);rep(i,n)a[i]=y[i]/gdeval[i];
    auto dfs=[&](auto&dfs,int l,int r,int idx)->fps<mint>{
        if(r-l==1){
            if(l>=n)return {0};
            return{a[l]};
        }
        int mid=(l+r)>>1;
        auto L=dfs(dfs,l,mid,idx*2);
        auto R=dfs(dfs,mid,r,idx*2+1);
        return L*tree[idx*2+1]+R*tree[idx*2];
    };
    auto ans=dfs(dfs,0,sz,1);
    return ans;
}
