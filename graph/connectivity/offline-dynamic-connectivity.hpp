#pragma once
#include "../../template.hpp"
namespace ryoku{
struct offline_dynamic_connectivity{
    int Q,q;
    vc<array<int,4>>ws;
    offline_dynamic_connectivity(int q):q(q){
        Q=1;
        while(Q<q)Q*=2;
    }
    void add_edge(int a,int b,int l,int r){
        if(l==r)return;
        ws.pb({a,b,l,r});
    }
    template<class Merge,class Undo,class Answer>
    void run(Merge merge,Undo undo,Answer f){
        vc<int>offset(2*Q+1);
        for(auto[a,b,l,r]:ws){
            l+=Q,r+=Q;
            while(l<r){
                if(l&1)offset[l+1]++,l++;
                if(r&1)r--,offset[r+1]++;
                l/=2,r/=2;
            }
        }
        rep(i,2*Q)offset[i+1]+=offset[i];
        vc<pii>edges(offset.back());
        {
            vc<int>pos=offset;
            for(auto[a,b,l,r]:ws){
                l+=Q,r+=Q;
                while(l<r){
                    if(l&1)edges[pos[l]++]={a,b},l++;
                    if(r&1)r--,edges[pos[r]++]={a,b};
                    l/=2,r/=2;
                }
            }
        }
        ws.clear();
        auto dfs=[&](auto&dfs,int idx)->void{
            REP(i,offset[idx],offset[idx+1]){
                auto[a,b]=edges[i];
                merge(a,b);
            }
            if(idx>=Q){
                int t=idx-Q;
                if(t<q)f(t);
            }else{
                dfs(dfs,idx*2);
                dfs(dfs,idx*2+1);
            }
            rep(i,offset[idx+1]-offset[idx])undo();
        };
        dfs(dfs,1);
    }
};
}