#pragma once
#include"../template.cpp"
struct Unweighted{
    Unweighted()=default;
    Unweighted(int){}
    operator int()const{return 1;}
};
template<bool is_directed,class T=Unweighted>
struct static_graph{
    constexpr static bool directed(){return is_directed;}
    using inverse_type=static_graph<is_directed^1,T>;
    struct edge{
        int from,to,id;
        [[no_unique_address]] T cost;
    };
    int n,m,added=0;
    mutable bool csr_built=false,inv_built=false;
    vc<edge>_all_edges;
    mutable vc<int>csr_start;
    mutable vc<edge>csr_edge;
    mutable vc<int>inv_start;
    mutable vc<edge>inv_edge;
    static_graph(int n):n(n),m(-1),csr_start(n+1){}
    static_graph(int n,int m):n(n),m(m),csr_start(n+1){_all_edges.reserve(m);}
    void add_edge(int a,int b,T cost=1){
        assert(0<=a&&a<n&&0<=b&&b<n);
        int id=(int)_all_edges.size();
        _all_edges.push_back({a,b,id,cost});
        csr_built=inv_built=false;
        if(++added==m)build();
    }
    void build()const{
        if(csr_built)return;
        csr_built=true;
        csr_start.assign(n+1,0);
        for(auto&e:_all_edges){
            csr_start[e.from+1]++;
            if constexpr(!is_directed)csr_start[e.to+1]++;
        }
        rep(i,n)csr_start[i+1]+=csr_start[i];
        csr_edge.resize(csr_start[n]);
        vc<int>now=csr_start;
        for(auto&e:_all_edges){
            csr_edge[now[e.from]++]=e;
            if constexpr(!is_directed)csr_edge[now[e.to]++]={e.to,e.from,e.id,e.cost};
        }
    }
    void build_inv()const{
        if(inv_built)return;
        inv_built=true;
        inv_start.assign(n+1,0);
        for(auto&e:_all_edges){
            inv_start[e.to+1]++;
            if constexpr(!is_directed)inv_start[e.from+1]++;
        }
        rep(i,n)inv_start[i+1]+=inv_start[i];
        inv_edge.resize(inv_start[n]);
        vc<int>now=inv_start;
        for(auto&e:_all_edges){
            inv_edge[now[e.to]++]={e.to,e.from,e.id,e.cost};
            if constexpr(!is_directed)inv_edge[now[e.from]++]=e;
        }
    }
    const vc<edge>&all_edges()const{return _all_edges;}
    int edge_size()const{return (int)_all_edges.size();}
    edge get_edge(int id)const{
        assert(0<=id&&id<edge_size());
        return _all_edges[id];
    }
    int out_deg(int u)const{assert(0<=u&&u<n);build();return csr_start[u+1]-csr_start[u];}
    int in_deg(int u)const{assert(0<=u&&u<n);build_inv();return inv_start[u+1]-inv_start[u];}
    int deg(int u)const{return out_deg(u);}
    auto operator[](int u){
        assert(0<=u&&u<n);build();
        return span<edge>(csr_edge.data()+csr_start[u],csr_edge.data()+csr_start[u+1]);
    }
    auto operator[](int u)const{
        assert(0<=u&&u<n);build();
        return span<const edge>(csr_edge.data()+csr_start[u],csr_edge.data()+csr_start[u+1]);
    }
    auto inv(int u){
        assert(0<=u&&u<n);build_inv();
        return span<edge>(inv_edge.data()+inv_start[u],inv_edge.data()+inv_start[u+1]);
    }
    auto inv(int u)const{
        assert(0<=u&&u<n);build_inv();
        return span<const edge>(inv_edge.data()+inv_start[u],inv_edge.data()+inv_start[u+1]);
    }
    int size()const{return n;}
    template<class F>vvc<F>adj()const{
        vvc<F>res(n,vc<F>(n));
        for(auto&e:all_edges()){
            res[e.from][e.to]=e.cost;
            if(directed()==false)res[e.to][e.from]=e.cost;
        }
        return res;
    }
    void clear(){
        added=0;
        csr_built=false;
        inv_built=false;
        _all_edges.clear();_all_edges.shrink_to_fit();
        csr_start.assign(n+1,0);csr_start.shrink_to_fit();
        csr_edge.clear();csr_edge.shrink_to_fit();
        inv_start.clear();inv_start.shrink_to_fit();
        inv_edge.clear();inv_edge.shrink_to_fit();
    }
    static_graph to_simple()const{
        static_graph res(n);
        vc<pair<int,int>>es;
        es.reserve(_all_edges.size());
        for(auto&e:_all_edges){
            if(e.from==e.to)continue;
            int u=e.from,v=e.to;
            if constexpr(!is_directed)if(u>v)std::swap(u,v);
            es.push_back({u,v});
        }
        std::sort(es.begin(),es.end());
        es.erase(std::unique(es.begin(),es.end()),es.end());
        for(auto&p:es)res.add_edge(p.first,p.second);
        res.build();
        return res;
    }
};
template<class T,class Graph>
pair<vc<int>,T>shortest_path(const Graph&g,int s,int t){
    int n=g.size();
    vc<T>md(n,numeric_limits<T>::max());
    vc<int>last(n,-1);
    smpq<pair<T,int>>que;
    md[s]=0;que.push({0,s});
    while(que.size()){
        auto [d,v]=que.top();que.pop();
        if(md[v]!=d)continue;
        for(auto&e:g[v]){
            if(chmin(md[e.to],d+e.cost))que.push({md[e.to],e.to}),last[e.to]=e.from;
        }
    }
    T ans=md[t];
    if(ans==numeric_limits<T>::max())return {{},{}};
    vc<int>path{t};
    while(s!=t){
        t=last[t];
        path.pb(t);
    }
    reverse(all(path));
    return {path,ans};
}
template<class Graph>
pair<vc<int>,vc<int>>cycle_detection(const Graph&g){
    {
        int n=g.size();
        vc<int>seen(n);
        vc<int>on(n);
        rep(i,n){
            if(seen[i])continue;
            vc<int>epath;
            vc<int>vpath;
            auto dfs=[&](auto&dfs,int u,int v,int eid)->pair<vc<int>,vc<int>>{
                on[u]=1;
                vpath.pb(u);
                for(auto&e:g[u]){
                    if(seen[e.to]==1)continue;
                    if(e.id==eid)continue;
                    if(!on[e.to]){
                        epath.pb(e.id);
                        auto rs=dfs(dfs,e.to,u,e.id);
                        if(rs.first.size())return rs;
                        epath.pop_back();
                    }else{
                        vc<int>res{};
                        vc<int>res2;
                        drep(i,vpath.size()){
                            res2.pb(vpath[i]);
                            if(vpath[i]==e.to)break;
                        }
                        DREP(i,(int)epath.size()-1,(int)epath.size()-(int)res2.size()+1){
                            res.pb(epath[i]);
                        }
                        reverse(all(res));reverse(all(res2));
                        res.pb(e.id);
                        return {res2,res};
                    }
                }
                vpath.pop_back();
                on[u]=0;
                seen[u]=1;
                return {};
            };
            auto res=dfs(dfs,i,-1,-1);
            if(res.first.size())return res;
        }
    }
    return {};
}