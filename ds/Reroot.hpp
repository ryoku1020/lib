#pragma  once
#include "../tree/base.hpp"
/*
struct Reroot{
    using V=Value;
    using E=Value;
    using Edge=Tree<>::Edge;
    static E merge(E a,E b){
    }
    static V put_vertex(E a,int v){

    }
    static E put_edge(V a,Edge e){

    }
    static E id(){

    }
};*/
template<class Reroot,class T=Unweighted>
struct Redp{
    using E=Reroot::E;
    using V=Reroot::V;
    using Edge=typename Tree<T>::Edge;
    using cost_t=typename Tree<T>::cost_t;
    Tree<T>t;
    vc<V>dp,ans;
    Redp(int n):t(n),dp(n),ans(n){assert(n>=0);}
    void add_edge(const Edge&e){
        t.add_edge(e);
    }
    void add_edge(int a,int b,cost_t cost=1,int id=-1){
        t.add_edge(a,b,cost,id);
    }
    vc<V>calc(){
        int n=t.n;
        if(n==0)return {};
        auto dfs=[&](auto&dfs,int u,int v)->void{
            E tmp=Reroot::id();
            for(auto&e:t[u]){
                if(e.to==v)continue;
                dfs(dfs,e.to,u);
                tmp=Reroot::merge(tmp,Reroot::put_edge(dp[e.to],e));
            }
            dp[u]=Reroot::put_vertex(tmp,u);
        };
        dfs(dfs,0,-1);
        auto dfs2=[&](auto&dfs2,int u,int v,E par)->void{
            auto s=t[u];
            int sz=s.size();
            vc<E>dps(sz);
            rep(i,sz){
                if(s[i].to!=v)dps[i]=Reroot::put_edge(dp[s[i].to],s[i]);
                else dps[i]=par;
            }
            vc<E>pref(sz+1,Reroot::id()),suff(sz+1,Reroot::id());
            rep(i,sz)pref[i+1]=Reroot::merge(pref[i],dps[i]);
            drep(i,sz)suff[i]=Reroot::merge(suff[i+1],dps[i]);
            ans[u]=Reroot::put_vertex(pref[sz],u);
            rep(i,sz){
                if(s[i].to!=v)
                    dfs2(dfs2,s[i].to,u,
                        Reroot::put_edge(
                            Reroot::put_vertex(Reroot::merge(pref[i],suff[i+1]),u),
                            s[i]));
            }
        };
        dfs2(dfs2,0,-1,Reroot::id());
        return ans;
    }
};
