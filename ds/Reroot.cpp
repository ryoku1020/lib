#pragma  once
#include"../template.cpp"
/*
struct Reroot{
    using V=hoge;
    using E=hoge;
    static E merge(E a,E b){
    }
    static V put_vertex(E a,int v){
    
    }
    static E put_edge(V a,int e){
    
    }
    static E id(){
    
    }
};*/
template<class Reroot>
struct Redp{
    using E=Reroot::E;
    using V=Reroot::V;
    vc<V>dp;
    vc<V>ans;
    vvc<pair<int,int>>g;
    Redp(int n):g(n),dp(n),ans(n){}
    void ae(int a,int b,int idx,int xdi){
        g[a].push_back({b,idx});
        g[b].push_back({a,xdi});
    }
    vc<V>calc(){
        auto dfs=[&](auto&dfs,int u,int v)->void{
            E tmp=Reroot::id();
            for(auto&[x,idx]:g[u]){
                if(x==v)continue;
                dfs(dfs,x,u);
                tmp=Reroot::merge(tmp,Reroot::put_edge(dp[x],idx));
            }
            dp[u]=Reroot::put_vertex(tmp,u);
        };
        dfs(dfs,0,-1);
        auto dfs2=[&](auto&dfs2,int u,int v,E par)->void{
            vc<E>dps{};
            REP(i,0,g[u].size()){
                if(g[u][i].first!=v)dps.push_back(Reroot::put_edge(dp[g[u][i].first],g[u][i].second));
                else dps.push_back(par);
            }
            vc<E>pref(dps.size()+1,Reroot::id()),suff(dps.size()+1,Reroot::id());
            rep(i,dps.size())pref[i+1]=Reroot::merge(pref[i],dps[i]);
            drep(i,dps.size())suff[i]=Reroot::merge(suff[i+1],dps[i]);
            ans[u]=Reroot::put_vertex(pref.back(),u);
            REP(i,0,g[u].size()){
                if(g[u][i].first!=v)
                dfs2(dfs2,g[u][i].first,u,
                Reroot::put_edge(Reroot::put_vertex(Reroot::merge(pref[i],suff[i+1]),u),g[u][i].second));
            }
        };
        dfs2(dfs2,0,-1,Reroot::id());
        return ans;
    }
};