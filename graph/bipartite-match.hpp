#pragma once
struct bipartite_matching{
    int l,r;
    vc<int>pm,qm;
    vvc<int>g;
    vc<int>dist;
    bipartite_matching(int l,int r):l(l),r(r){
        assert(l>=0&&r>=0);
        pm.assign(l,-1);
        qm.assign(r,-1);
        g.resize(l);
        dist.resize(l);
    }
    void add_edge(int a,int b){
        assert(0<=a&&a<l);
        assert(0<=b&&b<r);
        g[a].push_back(b);
    }
    bool bfs(){
        queue<int>que;
        bool find=0;
        fill(all(dist),-1);
        rep(i,l){
            if(pm[i]==-1){
                dist[i]=0;
                que.push(i);
            }
        }
        while(que.size()){
            auto u=que.front();que.pop();
            for(auto&x:g[u]){
                int nu=qm[x];
                if(nu==-1){
                    find=1;
                }else if(dist[nu]==-1){
                    dist[nu]=dist[u]+1;
                    que.push(nu);
                }
            }
        }
        return find;
    }
    bool dfs(int u){
        assert(0<=u&&u<l);
        for(auto&x:g[u]){
            int nu=qm[x];
            if(nu==-1||(dist[nu]==dist[u]+1&&dfs(nu))){
                qm[x]=u;
                pm[u]=x;
                return 1;
            }
        }
        dist[u]=-1;
        return 0;
    }
    vc<pii> work(){
        while(bfs()){
            rep(i,l)if(pm[i]==-1)dfs(i);
        }
        vc<pii>ans;rep(i,l)if(pm[i]!=-1)ans.pb({i,pm[i]});
        return ans;
    }
};
