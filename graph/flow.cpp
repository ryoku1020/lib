#pragma once
#include"../template.cpp"
template<class T>
struct flow{
    struct edge{
        int to,rev;T cap;
    };
    int n;
    vvc<edge>g;
    vc<int>level;
    vc<int>itr;
    T ans=0;
    flow(int n):n(n),g(n){}
    void ae(int a,int b,T cap){
        assert(0<=a&&a<n&&0<=b&&b<n);
        g[a].push_back({b,(int)g[b].size(),cap});
        g[b].push_back({a,(int)g[a].size()-1,0});
    }
    void bfs(int s){
        queue<int>que;que.push(s);
        level[s]=0;
        while(que.size()){
            auto p=que.front();que.pop();
            for(auto&e:g[p]){
                if(e.cap>0){
                    if(chmin(level[e.to],level[p]+1))que.push(e.to);
                }
            }
        }
    }
    bool find=1;
    int dfs(int u,T min_cap,int t){
        if(u==t){
            find=1;
            return min_cap;
        }
        REP(i,itr[u],g[u].size()){
            auto&e=g[u][i];
            if(level[u]+1==level[e.to]&&e.cap>0){
                T res=dfs(e.to,min(min_cap,e.cap),t);
                if(res){
                    e.cap-=res;
                    g[e.to][e.rev].cap+=res;
                    return res;
                }
            }
            itr[u]++;
        }
        return 0;
    }
    T work(int s,int t){
        while(find){
            find=0;
            level.assign(n,1e9);
            itr.assign(n,0);
            bfs(s);
            while(dfs(s,numeric_limits<T>::max(),t)){}
        }
        return ans;
    }
};