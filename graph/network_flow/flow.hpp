#pragma once
#include"../base.hpp"
template<class Cap>
struct flow{
    struct edge{
        int from,to,id;
        Cap cost;
    };
    vc<edge>edges;
    int n;
    flow(int n=0):n(n){
        assert(n>=0);
    }
    void add_edge(int a,int b,Cap cap){
        assert(0<=a&&a<n);
        assert(0<=b&&b<n);
        assert(cap>=0);
        if(a!=b)edges.push_back({a,b,(int)edges.size(),cap});
    }
    vc<Cap>_flow;
    Cap run(int s,int t){
        assert(0<=s&&s<n);
        assert(0<=t&&t<n);
        _flow.assign(edges.size(),0);
        Cap res=0;
        while(1){
            static_graph<1,edge>g(n);
            for(auto&e:edges){
                Cap c1=e.cost-_flow[e.id];
                Cap c2=_flow[e.id];
                if(c1>0)g.add_edge({e.from,e.to,e.id,c1});
                if(c2>0)g.add_edge({e.to,e.from,e.id,c2});
            }
            vc<int>level(n,-1);
            queue<int>que;que.push(s);level[s]=0;
            while(que.size()){
                int v=que.front();que.pop();
                for(auto&e:g[v])if(level[e.to]==-1&&e.cost>0){
                    level[e.to]=level[v]+1;
                    que.push(e.to);
                }
            }
            if(level[t]==-1)break;
            vc<int>itr(n,0);
            auto dfs=[&](auto self,int v,Cap f)->Cap{
                if(v==t)return f;
                int sz=g[v].size();
                for(int&i=itr[v];i<sz;i++){
                    auto&e=g[v][i];
                    if(level[v]<level[e.to]&&e.cost>0){
                        Cap d=self(self,e.to,min(f,e.cost));
                            if(d>0){
                                e.cost-=d;
                            if(v==edges[e.id].from)_flow[e.id]+=d;
                            else _flow[e.id]-=d;
                            return d;
                        }
                    }
                }
                return 0;
            };
            while(Cap f=dfs(dfs,s,numeric_limits<Cap>::max()))res+=f;
        }
        return res;
    }
    vc<tuple<int,int,int,Cap>>info(){
        assert(_flow.size()==edges.size());
        vc<tuple<int,int,int,Cap>>res;
        rep(i,edges.size())res.push_back({edges[i].from,edges[i].to,edges[i].id,_flow[i]});
        return res;
    }
    vc<bool>min_cut(int s){
        assert(0<=s&&s<n);
        assert(_flow.size()==edges.size());
        static_graph<1,edge>g(n);
        for(auto&e:edges){
            Cap c1=e.cost-_flow[e.id];
            Cap c2=_flow[e.id];
            if(c1>0)g.add_edge({e.from,e.to,e.id,c1});
            if(c2>0)g.add_edge({e.to,e.from,e.id,c2});
        }
        vc<bool>res(n,false);
        queue<int>que;que.push(s);
        res[s]=true;
        while(que.size()){
            auto u=que.front();que.pop();
            for(auto&e:g[u]){
                if(e.cost>0&&!res[e.to]){
                    res[e.to]=true;
                    que.push(e.to);
                }
            }
        }
        return res;
    }
};
