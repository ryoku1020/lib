#pragma once
#include"../ds/fastset.hpp"
vvc<int>cographdecomposition(int n,vc<pair<int,int>>non_edge){
    assert(n>=0);
    FastSet st(n);rep(i,n)st.insert(i);
    vc<vc<int>>no(n);for(auto&[a,b]:non_edge){
        assert(0<=a&&a<n);
        assert(0<=b&&b<n);
        no[a].pb(b);
        no[b].pb(a);
    }rep(i,n)no[i].pb(i);
    rep(i,n)sort(all(no[i]));
    auto count=[&](int p,int x){
        auto itr=lower_bound(all(no[p]),x);
        return (itr!=no[p].end()&&*itr==x);
    };
    vvc<int>res;
    rep(i,n){
        if(st.count(i)){
            vc<int>last;
            queue<int>que;que.push(i);st.erase(i);
            while(que.size()){
                auto p=que.front();que.pop();
                last.pb(p);
                int np=0;
                while(1){
                    int nxt=st.next(np);
                    if(nxt==n)break;
                    if(!count(p,nxt)){
                        que.push(nxt);
                        st.erase(nxt);
                    }
                    np=nxt+1;
                }
            }
            res.pb(last);
        }
    }
    return res;
}
