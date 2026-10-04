#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class G>
struct formatter<lowlink<G>>{
    static void print(ostream&os,const lowlink<G>&ll){
        os<<"lowlink n="<<ll.n<<"\n  v      ord low parent_edge";
        size_t n=min<size_t>(ll.n,config.max_graph_vertices);
        for(size_t v=0;v<n;v++)os<<"\n  "<<setw(6)<<v<<setw(5)<<ll.ord[v]<<setw(4)<<ll.low[v]<<setw(12)<<ll.parid[v];
        vector<int>bridges;
        auto copy=ll;
        for(int id=0;id<copy.g.edge_size();id++)if(copy.isbridge(id))bridges.push_back(id);
        os<<"\nbridges = ";internal::print_value(os,bridges,0);
    }
};
template<class G>
struct formatter<bcc_view<lowlink<G>>>{
    static void print(ostream&os,const bcc_view<lowlink<G>>&view){
        auto copy=view.value;
        auto edge_components=copy.twoedge_component();
        auto vertex_components=copy.twovertex_component();
        os<<"lowlink components\nvertex -> 2-edge-component = ";
        internal::print_value(os,edge_components.toid,0);
        os<<"\nblocks (edge ids) = ";internal::print_value(os,vertex_components.egs,0);
        os<<"\nblock-cut tree = ";internal::print_value(os,vertex_components.comp,0);
    }
};
}
