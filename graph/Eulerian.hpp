#pragma once

//(頂点列,edge 列)
template<class Graph>
optional<pair<vc<int>,vc<typename Graph::Edge>>>eulerian(const Graph&g){
    if(g.edge_size()==0){
        return make_pair(vc<int>{0},vc<typename Graph::Edge>{});
    }
    int n=g.size();
    int S;
    bool is_cycle=false;
    if(Graph::directed()==false){
        vc<int>odd,even;
        rep(i,n){
            if(g[i].size()==0)continue;
            if(g[i].size()%2)odd.pb(i);
            else even.pb(i);
        }
        if(odd.size()==0&&even.size())S=even[0],is_cycle=1;
        else if(odd.size()==2){
            S=odd[0];
        }else return nullopt;
    }else{
        is_cycle=1;
        rep(i,n){
            is_cycle&=g.in_deg(i)==g.out_deg(i);
        }
        if(is_cycle){
            rep(i,n)if(g[i].size())S=i;
        }
        else{
            S=-1;
            int seen=0;
            rep(i,n){
                if(g.in_deg(i)==g.out_deg(i))continue;
                else if(g.in_deg(i)+1==g.out_deg(i)){
                    if(S==-1)S=i;
                    else return nullopt;
                }else if(g.in_deg(i)==g.out_deg(i)+1){
                    if(!chmax(seen,1))return nullopt;
                }else return nullopt;
            }
            if(!seen)return nullopt;
            if(S<0)return nullopt;
        }
    }
    {
        vc<typename Graph::Edge>trail;
        vc<int>used(g.edge_size());
        vc<int>front_edge(n);
        auto dfs=[&](auto&dfs,int u)->void{
            while(front_edge[u]<g[u].size()){
                auto e=g[u][front_edge[u]++];
                if(used[e.id])continue;
                used[e.id]=1;
                dfs(dfs,e.to);
                trail.pb(e);
            }
        };
        dfs(dfs,S);
        reverse(all(trail));
        vc<int>vs{S};for(auto&x:trail)vs.pb(x.to);
        if(trail.size()==g.edge_size()){
            return make_pair(vs,trail);
        }else return nullopt;
    }
}