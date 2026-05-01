#pragma once
#include"../template.hpp"
template<class G>
vc<int>scc(const G& g){
    assert(G::directed()==true);
    int n=g.size();
    vc<int>ord,v1(n,0),v2(n,0);
    // 第1DFS: 後順記録 (反復版)
    rep(i,n){
        if(v1[i])continue;
        vc<pair<int,int>>st; // (node, next_edge_idx)
        v1[i]=1;
        st.push_back({i,0});
        while(!st.empty()){
            int u=st.back().first;
            int idx=st.back().second;
            auto s=g[u];
            bool pushed=false;
            while(idx<(int)s.size()){
                int v=s[idx++].to;
                if(!v1[v]){
                    st.back().second=idx;
                    v1[v]=1;
                    st.push_back({v,0});
                    pushed=true;
                    break;
                }
            }
            if(!pushed){
                ord.pb(u);
                st.pop_back();
            }
        }
    }
    reverse(all(ord));
    vc<int>res(n);
    int cnt=0;
    // 第2DFS: 逆辺をたどる (反復版)
    for(int x:ord){
        if(v2[x])continue;
        vc<int>st;
        v2[x]=1;res[x]=cnt;
        st.push_back(x);
        while(!st.empty()){
            int u=st.back();st.pop_back();
            for(auto&e:g.inv(u))if(!v2[e.to]){
                v2[e.to]=1;res[e.to]=cnt;
                st.push_back(e.to);
            }
        }
        ++cnt;
    }
    return res;
}