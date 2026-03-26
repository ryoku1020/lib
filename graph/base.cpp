#pragma 
#include"../template.cpp"
template<bool is_directed,bool use_inv,class T=int>
struct static_graph{
    struct edge{
        int from,to,id;
        T cost;
    };
    int n,built=0;
    vc<int>csr_start;
    vc<edge>csr_edge;
    [[no_unique_address]]conditional_t<use_inv,vc<int>,int>inv_start;
    [[no_unique_address]]conditional_t<use_inv,vc<edge>,int>inv_edge;
    vector<tuple<int,int,T,int>>tmp_edge;
    vc<edge>all_edges;
    int m;
    static_graph(int n):n(n),csr_start(n+1),m(-1){if constexpr(use_inv)inv_start.assign(n+1,0);}
    static_graph(int n,int m):n(n),csr_start(n+1),m(m){
        if constexpr(use_inv)inv_start.assign(n+1,0);
        tmp_edge.reserve(m);
        if(m==0)build();
    }
    int added=0;
    void add_edge(int a,int b,T cost=1){
        assert(0<=a&&a<n&&0<=b&&b<n);
        tmp_edge.push_back({a,b,cost,added});
        if((++added)==m)build();
    }
    void build(){
        if(built)return;
        built=1;
        all_edges.resize(added); 
        for(auto&[a,b,w,id]:tmp_edge){
            all_edges[id]={a,b,id,w};
            csr_start[a+1]++;
            if constexpr(use_inv)inv_start[b+1]++;
            if constexpr(!is_directed){
                csr_start[b+1]++;
                if constexpr(use_inv)inv_start[a+1]++;
            }
        }
        rep(i,n){
            csr_start[i+1]+=csr_start[i];
            if constexpr(use_inv)inv_start[i+1]+=inv_start[i];
        }
        csr_edge.resize(csr_start[n]);
        vc<int>now_s=csr_start;
        if constexpr(use_inv){
            inv_edge.resize(inv_start[n]);
            vc<int>now_i=inv_start;
            for(auto&[a,b,w,id]:tmp_edge){
                csr_edge[now_s[a]++]={a,b,id,w};
                inv_edge[now_i[b]++]={b,a,id,w};
                if constexpr(!is_directed){
                    csr_edge[now_s[b]++]={b,a,id,w};
                    inv_edge[now_i[a]++]={a,b,id,w};
                }
            }
        }else{
            for(auto&[a,b,w,id]:tmp_edge){
                csr_edge[now_s[a]++]={a,b,id,w};
                if constexpr(!is_directed)csr_edge[now_s[b]++]={b,a,id,w};
            }
        }
        tmp_edge.clear();
    }
    edge get_edge(int id)const{
        assert(built&&0<=id&&id<int(all_edges.size()));
        return all_edges[id];
    }
    int deg(int u)const{assert(built);return csr_start[u+1]-csr_start[u];}
    int in_deg(int u)const{
        static_assert(use_inv);
        assert(built);return inv_start[u+1]-inv_start[u];
    }
    auto operator[](int u){
        assert(built);
        return span<edge>(csr_edge.data()+csr_start[u],csr_edge.data()+csr_start[u+1]);
    }
    auto operator[](int u)const{
        assert(built);
        return span<const edge>(csr_edge.data()+csr_start[u],csr_edge.data()+csr_start[u+1]);
    }
    auto inv(int u){
        static_assert(use_inv);
        assert(built);
        return span<edge>(inv_edge.data()+inv_start[u],inv_edge.data()+inv_start[u+1]);
    }
    auto inv(int u)const{
        static_assert(use_inv);
        assert(built);
        return span<const edge>(inv_edge.data()+inv_start[u],inv_edge.data()+inv_start[u+1]);
    }
    int size()const{return n;}
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