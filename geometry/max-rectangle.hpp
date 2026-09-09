#pragma once
#include"../tree/cartesian-tree.hpp"
//v[i]=1 or 0 で 1 のみからなる極大長方形
template<class F>
pair<array<int,4>,int>max_rectangle(vvc<int>v,F eval){
    int h=v.size(),w=v[0].size();
    vc<int>hi(w);
    ll ans=0;
    array<int,4>res{0,-1,0,-1};
    rep(hr,h){
        rep(j,w){
            if(v[hr][j]==0)hi[j]=0;
            else hi[j]++;
        }
        auto[t,root]=cartesian_tree<1>(hi);
        auto dfs=[&](auto&dfs,int u,int p)->pii{
            int l=u,r=u;
            for(auto&e:t[u]){
                if(e.to==p)continue;
                auto s=dfs(dfs,e.to,u);
                chmin(l,s.fi),chmax(r,s.se);
            }
            if(chmax(ans,eval(l,r,hr-hi[u]+1,hr))){
                res={l,r,int(hr-hi[u]+1),(int)hr};
            }
            return{l,r};
        };
        dfs(dfs,root,-1);
    }
    return{res,ans};
}
pair<array<int,4>,int>max_rectangle(vvc<int>v){
    return max_rectangle(std::move(v),[](int xl,int xr,int yl,int yr){
        return (xr-xl+1)*(yr-yl+1);
    });
}