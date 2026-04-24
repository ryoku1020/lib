#pragma once
#include"base.hpp"
template<class Cap,class Cost>
struct MinCostFlow{
    struct Edge{
        int from,to,id;
        Cap cap;
        Cost cost;
    };
    vc<Edge>edge;
    int n;
    MinCostFlow(int n=0):n(n){}
    void add_edge(int a,int b,Cap cap,Cost cost){
        assert(0<=a&&a<n);
        assert(0<=b&&b<n);
        assert(cost>=0);
        assert(cap>=0);
        if(a!=b)edge.push_back({a,b,(int)edge.size(),cap,cost});
    }
    vc<Cap>flow;
    optional<Cost>run(int s,int t,Cap target){
        assert(0<=s&&s<n);
        assert(0<=t&&t<n);
        flow.assign(edge.size(),0);
        vc<Cost>pot(n);
        Cost res=0;
        while(target){
            static_graph<1,Edge>g(n);
            for(auto e:edge){
                auto e1=e,e2=e;
                swap(e2.from,e2.to);
                e1.cap=e.cap-flow[e.id];
                e2.cap=flow[e.id];e2.cost=-e2.cost;
                if(e1.cap)g.add_edge(e1);
                if(e2.cap)g.add_edge(e2);
            }
            vc<Cost>md(n,numeric_limits<Cost>::max());
            smpq<pair<Cost,int>>que;que.push({0,s});md[s]=0;
            vc<Edge>pre(n);
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
            if(md[t]==numeric_limits<Cost>::max())return nullopt;
            int now=t;
            vc<Edge>used;
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
                bool is_rev=e.from!=edge[e.id].from;
                if(is_rev)flow[e.id]-=new_flow;
                else flow[e.id]+=new_flow;
            }
            rep(i,n)if(md[i]!=numeric_limits<Cost>::max())pot[i]+=md[i];
        }
        return res;
    }
    vc<tuple<int,int,int,Cap>>Info(){
        vc<tuple<int,int,int,Cap>>res;
        rep(i,edge.size()){
            res.push_back(tuple<int,int,int,Cap>{edge[i].from,edge[i].to,edge[i].id,flow[i]});
        }
        return res;
    }
};