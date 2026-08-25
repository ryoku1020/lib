#pragma  once
#include "../tree/base.hpp"
/*
struct reroot{
    using V=Value;
    using E=Value;
    using edge=tree<>::edge;
    static E merge(E a,E b){
    }
    static V put_vertex(E a,int v){

    }
    static E put_edge(V a,edge e){

    }
    static E id(){

    }
};*/
template<class reroot,class T=unweighted>
struct redp{
    using E=reroot::E;
    using V=reroot::V;
    using edge=typename tree<T>::edge;
    using cost_t=typename tree<T>::cost_t;
    tree<T>t;
    vc<V>dp,ans;
    redp(int n):t(n),dp(n),ans(n){assert(n>=0);}
    void add_edge(const edge&e){
        t.add_edge(e);
    }
    void add_edge(int a,int b,cost_t cost=1,int id=-1){
        t.add_edge(a,b,cost,id);
    }
    vc<V>calc(){
        int n=t.n;
        if(n==0)return {};
        auto dfs=[&](auto&dfs,int u,int v)->void{
            E tmp=reroot::id();
            for(auto&e:t[u]){
                if(e.to==v)continue;
                dfs(dfs,e.to,u);
                tmp=reroot::merge(tmp,reroot::put_edge(dp[e.to],e));
            }
            dp[u]=reroot::put_vertex(tmp,u);
        };
        dfs(dfs,0,-1);
        auto dfs2=[&](auto&dfs2,int u,int v,E par)->void{
            auto s=t[u];
            int sz=s.size();
            vc<E>dps(sz);
            rep(i,sz){
                if(s[i].to!=v)dps[i]=reroot::put_edge(dp[s[i].to],s[i]);
                else dps[i]=par;
            }
            vc<E>pref(sz+1,reroot::id()),suff(sz+1,reroot::id());
            rep(i,sz)pref[i+1]=reroot::merge(pref[i],dps[i]);
            drep(i,sz)suff[i]=reroot::merge(suff[i+1],dps[i]);
            ans[u]=reroot::put_vertex(pref[sz],u);
            rep(i,sz){
                if(s[i].to!=v)
                    dfs2(dfs2,s[i].to,u,
                        reroot::put_edge(
                            reroot::put_vertex(reroot::merge(pref[i],suff[i+1]),u),
                            s[i]));
            }
        };
        dfs2(dfs2,0,-1,reroot::id());
        return ans;
    }
};
