#pragma once
struct CsrGraph{
    vc<int>row_ptr;
    vc<int>col_indices;
    vc<pair<int,int>>edges;
    struct RowView{
        int*ptr_b;
        int*ptr_e;
        int*begin(){return ptr_b;}
        int*end(){return ptr_e;}
        int& operator[](size_t i){return ptr_b[i];}
        const int& operator[](size_t i)const{return ptr_b[i];}
        size_t size()const{return ptr_e-ptr_b;}
        bool empty()const{return ptr_b==ptr_e;}    
    };
    CsrGraph(int n):row_ptr(n+1,0){
        assert(n>=0);
    }
    void add_edge(int u,int v){
        assert(!built);
        assert(0<=u&&u+1<(int)row_ptr.size());
        assert(0<=v);
        edges.push_back({u,v});
    }
    bool built=0;
    void build(){
        if(built)return;
        built=1;
        for(const auto&e:edges)row_ptr[e.first+1]++;
        for(int i=0;i<row_ptr.size()-1;++i)row_ptr[i+1]+=row_ptr[i];
        col_indices.assign(edges.size()+1,0);
        vc<int>cur=row_ptr;
        for(const auto&e:edges)col_indices[cur[e.first]++]=e.second;
        edges.clear();
        edges.shrink_to_fit();
    }
    int empty(int u){
        assert(0<=u&&u+1<(int)row_ptr.size());
        build();
        return row_ptr[u+1]==row_ptr[u];
    }
    RowView operator[](int u){
        assert(0<=u&&u+1<(int)row_ptr.size());
        build();
        return{&col_indices[row_ptr[u]],&col_indices[row_ptr[u+1]]};
    }
};
