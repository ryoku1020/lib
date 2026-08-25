#pragma once
#include"../base.hpp"
template<class Cap,class Cost>
struct min_cost_flow{
    struct edge{
        int from,to,id;
        Cap cap;
        Cost cost;
    };
    vc<edge>edges;
    int n;
    min_cost_flow(int n=0):n(n){assert(n>=0);}
    void add_edge(int a,int b,Cap cap,Cost cost){
        assert(0<=a&&a<n);
        assert(0<=b&&b<n);
        assert(cost>=0);
        assert(cap>=0);
        if(a!=b)edges.push_back({a,b,(int)edges.size(),cap,cost});
    }
    vc<Cap>flow;
    pair<Cost,Cap>run(int s,int t,Cap target){
        assert(0<=s&&s<n);
        assert(0<=t&&t<n);
        assert(target>=0);
        flow.assign(edges.size(),0);
        vc<Cost>pot(n);
        Cost res=0;
        Cap flow=0;
        while(target){
            static_graph<1,edge>g(n);
            for(auto e:edges){
                auto e1=e,e2=e;
                swap(e2.from,e2.to);
                e1.cap=e.cap-flow[e.id];
                e2.cap=flow[e.id];e2.cost=-e2.cost;
                if(e1.cap)g.add_edge(e1);
                if(e2.cap)g.add_edge(e2);
            }
            vc<Cost>md(n,numeric_limits<Cost>::max());
            smpq<pair<Cost,int>>que;que.push({0,s});md[s]=0;
            vc<edge>pre(n);
            while(que.size()){
                auto [d,v]=que.top();que.pop();
                if(md[v]!=d)continue;
                for(auto&e:g[v]){
                    if(chmin(md[e.to],md[v]+e.cost-pot[e.to]+pot[v])){
                        que.push({md[e.to],e.to});
                        pre[e.to]=e;
                    }
                }
            }
            if(md[t]==numeric_limits<Cost>::max())return {res,flow};
            int now=t;
            vc<edge>used;
            while(now!=s){
                used.push_back(pre[now]);
                now=pre[now].from;
            }
            Cap new_flow=target;
            for(auto&e:used){
                chmin(new_flow,e.cap);
            }
            target-=new_flow;
            for(auto&e:used){
                res+=e.cost*new_flow;
                bool is_rev=e.from!=edges[e.id].from;
                if(is_rev)flow[e.id]-=new_flow;
                else flow[e.id]+=new_flow;
            }
            flow+=new_flow;
            rep(i,n)if(md[i]!=numeric_limits<Cost>::max())pot[i]+=md[i];
        }
        return {res,flow};
    }
    vc<tuple<int,int,int,Cap>>info(){
        assert(flow.size()==edges.size());
        vc<tuple<int,int,int,Cap>>res;
        rep(i,edges.size()){
            res.push_back(tuple<int,int,int,Cap>{edges[i].from,edges[i].to,edges[i].id,flow[i]});
        }
        return res;
    }
};
