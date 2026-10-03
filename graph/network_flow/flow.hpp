#pragma once
template<class Cap>
struct flow{
    struct edge{
        int from,to,id,rev;
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
        if(a!=b)edges.push_back({a,b,(int)edges.size(),-1,cap});
    }
    vc<Cap>_flow;
    vvc<edge>g;
    Cap run(int s,int t){
        assert(0<=s&&s<n);
        assert(0<=t&&t<n);
        _flow.assign(edges.size(),0);
        g.assign(n,{});
        for(auto&e:edges){
            int a=g[e.from].size(),b=g[e.to].size();
            g[e.from].push_back({e.from,e.to,e.id,b,e.cost});
            g[e.to].push_back({e.to,e.from,e.id,a,0});
        }
        Cap res=0;
        while(1){
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
                for(int&i=itr[v];i<(int)g[v].size();i++){
                    auto&e=g[v][i];
                    if(level[v]<level[e.to]&&e.cost>0){
                        Cap d=self(self,e.to,min(f,e.cost));
                        if(d>0){
                            e.cost-=d;
                            g[e.to][e.rev].cost+=d;
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