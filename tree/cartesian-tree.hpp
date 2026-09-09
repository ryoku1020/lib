#pragma once
#include"base.hpp"
template<int mintop,class T>
pair<tree<unweighted>,int>cartesian_tree(const vc<T>&v){
    assert(v.size());
    int n=v.size();
    tree<unweighted>t(n);
    vc<int>st;
    rep(i,n){
        int last=-1;
        while(st.size()&&(mintop?v[st.back()]>=v[i]:v[st.back()]<=v[i])){
            int x=st.back();
            st.pop_back();
            if(last>=0)t.add_edge(x,last);
            last=x;
        }
        if(last>=0)t.add_edge(last,i);
        st.push_back(i);
    }
    REP(i,1,st.size())t.add_edge(st[i-1],st[i]);
    return{t,st[0]};
}
