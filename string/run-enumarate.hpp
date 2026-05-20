#pragma once
#include"z-algorithm.hpp"
vc<array<int,3>>RunEnumerate(string s){
    assert(s.size()<=numeric_limits<int>::max());
    if(s.empty())return {};
    unordered_map<ll,int>ma;
    int K=random_device{}();
    rep(i,2){
        auto update=[&](int l,int r,int t){
            if(r-l<2*t)return;
            if(s[r]==s[r-t])return;
            if(l&&s[l-1]==s[l-1+t])return;
            if(i)l=s.size()-l,r=s.size()-r,swap(l,r);
            ll target=ll(l)<<32;target+=r;
            if(!ma.count(target^K)||ma[target^K]>t)ma[target^K]=t;
        };
        auto dfs=[&](auto&dfs,int l,int r)->void{
            if(r-l<=1)return;
            int mid=(l+r+i)>>1;
            dfs(dfs,l,mid);
            dfs(dfs,mid,r);
            string s1=string(s.begin()+l,s.begin()+mid);reverse(all(s1));
            string s2=string(s.begin()+mid,s.begin()+r);s2+='#';s2+=string(s.begin()+l,s.begin()+r);
            auto z1=ZAlgorithm(s1);
            auto z2=ZAlgorithm(s2);
            for(int w=1;w<=mid-l;w++){
                int L=mid-w;//[L,mid)
                int left=L;if(w!=mid-l)left-=z1[w];
                int right=z2[r-mid+1+L-l];
                update(left,mid+right,w);
            }
        };
        dfs(dfs,0,s.size());
        reverse(all(s));
    }
    vc<array<int,3>>res;
    for(auto&[X,y]:ma){
        auto x=X^K;
        res.push_back({y,int(x/(1ll<<32)),int(x%(1ll<<32))});
    }
    return res;
}
