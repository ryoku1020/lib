#pragma once
#include"../template.hpp"
struct Unweighted{
    Unweighted()=default;
    Unweighted(int){}
    operator int()const{return 1;}
};
template<class T=Unweighted>
struct edge{
    int from,to,id;
    [[no_unique_address]] T cost;
    #ifdef LOCAL
    friend ostream&operator<<(ostream&os,const edge&e){
        return os<<"{from:"<<e.from<<",to:"<<e.to<<",id:"<<e.id<<",cost:"<<e.cost<<"}";
    }
    #endif
};
template<bool is_directed,class T=Unweighted>
struct static_graph{
    constexpr static bool directed(){return is_directed;}
using edge_type=edge<T>;
private:
    int n,m,added=0;
    mutable bool csr_built=false,inv_built=false;
    vc<edge_type>_all_edges;
    mutable vc<int>csr_start;
    mutable vc<edge_type>csr_edge;
    mutable vc<int>inv_start;
    mutable vc<edge_type>inv_edge;
public:
    static_graph(int n):n(n),m(-1),csr_start(n+1){}
    static_graph(int n,int m):n(n),m(m),csr_start(n+1){_all_edges.reserve(m);}
    void add_edge(int a,int b,T cost=1,int id=-1){
        assert(0<=a&&a<n&&0<=b&&b<n);
        if(id==-1)id=(int)_all_edges.size();
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
    const vc<edge_type>&all_edges()const{return _all_edges;}
    int edge_size()const{return (int)_all_edges.size();}
    edge_type get_edge(int id)const{
        assert(0<=id&&id<edge_size());
        return _all_edges[id];
    }
    int out_deg(int u)const{assert(0<=u&&u<n);build();return csr_start[u+1]-csr_start[u];}
    int in_deg(int u)const{assert(0<=u&&u<n);build_inv();return inv_start[u+1]-inv_start[u];}
    int deg(int u)const{return out_deg(u);}
    template<class E>
    struct span {
        E* l; E* r;
        E* begin() const { return l; }
        E* end() const { return r; }
        int size() const { return r - l; }
        E& operator[](int i) { return l[i]; }
        const E& operator[](int i) const { return l[i]; }
    };
    auto operator[](int u){
        assert(0<=u&&u<n);build();
        return span<edge_type>{csr_edge.data()+csr_start[u],csr_edge.data()+csr_start[u+1]};
    }
    auto operator[](int u)const{
        assert(0<=u&&u<n);build();
        return span<const edge_type>{csr_edge.data()+csr_start[u],csr_edge.data()+csr_start[u+1]};
    }
    auto inv(int u){
        assert(0<=u&&u<n);build_inv();
        return span<edge_type>{inv_edge.data()+inv_start[u],inv_edge.data()+inv_start[u+1]};
    }
    auto inv(int u)const{
        assert(0<=u&&u<n);build_inv();
        return span<const edge_type>{inv_edge.data()+inv_start[u],inv_edge.data()+inv_start[u+1]};
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
    template<class F>
    void sort(int i,F f){
        assert(0<=i&&i<n);
        build();
        sort(csr_edge.begin()+csr_start[i],csr_edge.begin()+csr_start[i+1],f);
    }
    template<class F>
    void sort_inv(int i,F f){
        assert(0<=i&&i<n);
        build_inv();
        sort(inv_edge.begin()+inv_start[i],inv_edge.begin()+inv_start[i+1],f);
    }
    template<class F>
    static_graph<is_directed,T>extract(F f)const{
        static_graph<is_directed,T>res(n);
        for(auto&e:_all_edges)if(f(e))res.add_edge(e.from,e.to,e.cost,e.id);
        return res;
    }
    template<class F>
    static_graph<1,T>reorder(F f)const{
        static_graph<1,T>res(n);
        for(auto&e:_all_edges){
            if(f(e))res.add_edge(e.from,e.to,e.cost,e.id);
            else res.add_edge(e.to,e.from,e.cost,e.id);
        }
        return res;
    }
};