#pragma once
struct unweighted{
    unweighted()=default;
    unweighted(int){}
    operator int()const{return 1;}
};
template<class T=unweighted>
struct edge{
    int from,to,id;
    [[no_unique_address]]T cost;
#ifdef LOCAL
    friend ostream&operator<<(ostream&os,const edge&e){
        return os<<"{from:"<<e.from<<",to:"<<e.to<<",id:"<<e.id<<",cost:"<<e.cost<<"}";
    }
#endif
};
template<bool is_directed,class T=unweighted>
struct static_graph{
    constexpr static bool directed(){return is_directed;}
    using edge=::edge<T>;
    using cost_t=T;
private:
    int n;
    mutable bool built=false,inv_built=false;
    vc<edge>edges;
    mutable vc<int>start,inv_start;
    mutable vc<edge>csr,inv_csr;
public:
    static_graph(int n):n(n),start(n+1),inv_start(n+1){assert(n>=0);}
    static_graph(int n,int m):static_graph(n){assert(m>=0);edges.reserve(m);}
    void resize(int size){
        assert(n<=size&&!built);
        assert(!inv_built);
        n=size;
        start.resize(n+1);
        inv_start.resize(n+1);
    }
    void add_edge(const edge&e){
        assert(!built&&!inv_built);
        assert(0<=e.from&&e.from<n&&0<=e.to&&e.to<n);
        edges.pb(e);
    }
    void add_edge(int a,int b,cost_t cost=1,int id=-1){
        assert(!built&&!inv_built);
        assert(0<=a&&a<n&&0<=b&&b<n);
        if(id==-1)id=edges.size();
        edges.pb({a,b,id,cost});
    }
    template<int substract=0>
    void input(int m){
        assert(m>=0);
        rep(i,m){
            INT(a,b);
            a-=substract;b-=substract;
            add_edge(a,b);
        }
        build();
    }
    void build()const{
        if(built)return;
        built=true;
        start.assign(n+1,0);
        for(auto&e:edges){
            ++start[e.from];
            if constexpr(!is_directed)++start[e.to];
        }
        rep(i,n)start[i+1]+=start[i];
        csr.resize(start[n]);
        for(auto it=edges.rbegin();it!=edges.rend();++it){
            auto&e=*it;
            csr[--start[e.from]]=e;
            if constexpr(!is_directed)csr[--start[e.to]]={e.to,e.from,e.id,e.cost};
        }
    }
    void buildinv()const{
        if(inv_built)return;
        inv_start.assign(n+1,0);
        for(auto&e:edges){
            ++inv_start[e.to];
            if constexpr(!is_directed)++inv_start[e.from];
        }
        rep(i,n)inv_start[i+1]+=inv_start[i];
        inv_csr.resize(inv_start[n]);
        for(auto it=edges.rbegin();it!=edges.rend();++it){
            auto&e=*it;
            inv_csr[--inv_start[e.to]]={e.to,e.from,e.id,e.cost};
            if constexpr(!is_directed)inv_csr[--inv_start[e.from]]={e.from,e.to,e.id,e.cost};
        }
        inv_built=true;
    }
    auto operator[](int u){
        build();
        assert(0<=u&&u<n);
        return span<edge>(csr.data()+start[u],start[u+1]-start[u]);
    }

    auto operator[](int u)const{
        build();
        assert(0<=u&&u<n);
        return span<const edge>(csr.data()+start[u],start[u+1]-start[u]);
    }

    auto inv(int u){
        buildinv();
        assert(0<=u&&u<n);
        return span<edge>(inv_csr.data()+inv_start[u],inv_start[u+1]-inv_start[u]);
    }

    auto inv(int u)const{
        buildinv();
        assert(0<=u&&u<n);
        return span<const edge>(inv_csr.data()+inv_start[u],inv_start[u+1]-inv_start[u]);
    }

    const vc<edge>&all_edges()const{return edges;}
    int edge_size()const{return edges.size();}

    edge get_edge(int id)const{
        assert(0<=id&&id<edge_size());
        return edges[id];
    }
    int out_deg(int u)const{
        build();
        assert(0<=u&&u<n);
        return start[u+1]-start[u];
    }
    int in_deg(int u)const{
        buildinv();
        assert(0<=u&&u<n);
        return inv_start[u+1]-inv_start[u];
    }
    int deg(int u)const{return out_deg(u);}
    int size()const{return n;}
    template<class F>
    vvc<F>adj()const{
        vvc<F>res(n,vc<F>(n));
        for(auto&e:edges){
            res[e.from][e.to]=e.cost;
            if constexpr(!is_directed)res[e.to][e.from]=e.cost;
        }
        return res;
    }
    void clear(){
        built=false;
        inv_built=false;
        edges.clear();
        csr.clear();
        inv_csr.clear();
        start.assign(n+1,0);
        inv_start.assign(n+1,0);
    }
    template<class F>
    void sort(int i,F f){
        build();
        assert(0<=i&&i<n);
        std::sort(csr.begin()+start[i],csr.begin()+start[i+1],f);
    }
};
