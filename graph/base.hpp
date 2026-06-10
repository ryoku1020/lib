#pragma once
#include<type_traits>
struct Unweighted{
    Unweighted()=default;
    Unweighted(int){}
    operator int()const{return 1;}
};
template<class T=Unweighted>
struct Edge{
    int from,to,id;
    [[no_unique_address]] T cost;
    #ifdef LOCAL
    friend ostream&operator<<(ostream&os,const Edge&e){
        return os<<"{from:"<<e.from<<",to:"<<e.to<<",id:"<<e.id<<",cost:"<<e.cost<<"}";
    }
    #endif
};
template<class T,class=void>struct IsEdge:false_type{};
template<class T>struct IsEdge<T,void_t<decltype(declval<T>().from),decltype(declval<T>().to),decltype(declval<T>().id),decltype(declval<T>().cost)>>:true_type{};
struct EmptyStorage{};
template<bool is_directed,class T=Unweighted>
struct StaticGraph{
    constexpr static bool directed(){return is_directed;}
    using Edge=conditional_t<IsEdge<T>::value,T,::Edge<T>>;
    using cost_t=decltype(declval<Edge>().cost);
private:
    int n,m,added=0;
    mutable bool csr_built=false;
    [[no_unique_address]] mutable conditional_t<is_directed,bool,EmptyStorage> inv_built{};
    vc<Edge>_all_edges;
    mutable vc<int>csr_start;
    mutable vc<Edge>csr_edge;
    [[no_unique_address]] mutable conditional_t<is_directed,vc<int>,EmptyStorage>inv_start;
    [[no_unique_address]] mutable conditional_t<is_directed,vc<Edge>,EmptyStorage>inv_edge;
public:
    StaticGraph(int n):n(n),m(-1){assert(n>=0);csr_start.resize(n+1);}
    StaticGraph(int n,int m):n(n),m(m){assert(n>=0&&m>=0);csr_start.resize(n+1);_all_edges.reserve(m);}
    void add_edge(const Edge&e){
        assert(0<=e.from&&e.from<n&&0<=e.to&&e.to<n);
        assert(m==-1||added<m);
        _all_edges.push_back(e);
        csr_built=false;
        if constexpr(is_directed)inv_built=false;
        if(++added==m)build();
    }
    void add_edge(int a,int b,cost_t cost=1,int id=-1){
        assert(0<=a&&a<n&&0<=b&&b<n);
        assert(m==-1||added<m);
        if(id==-1)id=(int)_all_edges.size();
        _all_edges.push_back({a,b,id,cost});
        csr_built=false;
        if constexpr(is_directed)inv_built=false;
        if(++added==m)build();
    }
    template<int substract=0>
    void input(int edge_count){
        assert(edge_count>=0);
        rep(i,edge_count){
            INT(a,b);
            a-=substract;
            b-=substract;
            add_edge(a,b);
        }
    }
    void build()const{
        if(csr_built)return;
        csr_built=true;
        csr_start.assign(n+1,0);
        for(auto&e:_all_edges){
            csr_start[e.from]++;
            if constexpr(!is_directed)csr_start[e.to]++;
        }
        rep(i,n)csr_start[i+1]+=csr_start[i];
        csr_edge.resize(csr_start[n]);
        for(auto it=_all_edges.rbegin();it!=_all_edges.rend();++it){
            auto&e=*it;
            csr_edge[--csr_start[e.from]]=e;
            if constexpr(!is_directed)csr_edge[--csr_start[e.to]]={e.to,e.from,e.id,e.cost};
        }
    }
    void build_inv()const{
        if constexpr(!is_directed){
            build();
            return;
        }else{
            if(inv_built)return;
            inv_built=true;
            inv_start.assign(n+1,0);
            for(auto&e:_all_edges){
                inv_start[e.to]++;
            }
            rep(i,n)inv_start[i+1]+=inv_start[i];
            inv_edge.resize(inv_start[n]);
            for(auto it=_all_edges.rbegin();it!=_all_edges.rend();++it){
                auto&e=*it;
                inv_edge[--inv_start[e.to]]={e.to,e.from,e.id,e.cost};
            }
        }
    }
    const vc<Edge>&all_edges()const{return _all_edges;}
    int edge_size()const{return (int)_all_edges.size();}
    Edge get_edge(int id)const{
        assert(0<=id&&id<edge_size());
        return _all_edges[id];
    }
    int out_deg(int u)const{assert(0<=u&&u<n);build();return csr_start[u+1]-csr_start[u];}
    int in_deg(int u)const{
        assert(0<=u&&u<n);
        if constexpr(!is_directed){
            return out_deg(u);
        }else{
            build_inv();
            return inv_start[u+1]-inv_start[u];
        }
    }
    int deg(int u)const{return out_deg(u);}
    template<class E>
    struct Span{
        E*l; E* r;
        E*begin()const{return l;}
        E*end()const{return r;}
        int size()const{return r-l;}
        E&operator[](int i){return l[i];}
        const E&operator[](int i)const{return l[i];}
    };
    auto operator[](int u){
        assert(0<=u&&u<n);build();
        return Span<Edge>{csr_edge.data()+csr_start[u],csr_edge.data()+csr_start[u+1]};
    }
    auto operator[](int u)const{
        assert(0<=u&&u<n);build();
        return Span<const Edge>{csr_edge.data()+csr_start[u],csr_edge.data()+csr_start[u+1]};
    }
    auto inv(int u){
        assert(0<=u&&u<n);
        if constexpr(!is_directed){
            return (*this)[u];
        }else{
            build_inv();
            return Span<Edge>{inv_edge.data()+inv_start[u],inv_edge.data()+inv_start[u+1]};
        }
    }
    auto inv(int u)const{
        assert(0<=u&&u<n);
        if constexpr(!is_directed){
            return (*this)[u];
        }else{
            build_inv();
            return Span<const Edge>{inv_edge.data()+inv_start[u],inv_edge.data()+inv_start[u+1]};
        }
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
        if constexpr(is_directed)inv_built=false;
        _all_edges.clear();_all_edges.shrink_to_fit();
        csr_start.assign(n+1,0);csr_start.shrink_to_fit();
        csr_edge.clear();csr_edge.shrink_to_fit();
        if constexpr(is_directed){
            inv_start.clear();inv_start.shrink_to_fit();
            inv_edge.clear();inv_edge.shrink_to_fit();
        }
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
        if constexpr(!is_directed){
            build();
            sort(csr_edge.begin()+csr_start[i],csr_edge.begin()+csr_start[i+1],f);
            return;
        }
        build_inv();
        sort(inv_edge.begin()+inv_start[i],inv_edge.begin()+inv_start[i+1],f);
    }
    template<class F>
    StaticGraph<is_directed,T>extract(F f)const{
        StaticGraph<is_directed,T>res(n);
        for(auto&e:_all_edges)if(f(e))res.add_edge(e);
        return res;
    }
    template<class F>
    StaticGraph<1,T>reorder(F f)const{
        StaticGraph<1,T>res(n);
        for(auto&e:_all_edges){
            if(f(e))res.add_edge(e);
            else res.add_edge({e.to,e.from,e.id,e.cost});
        }
        return res;
    }
};
