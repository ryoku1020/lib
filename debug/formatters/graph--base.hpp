#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class T>
struct formatter<::ryoku::edge<T>>{
    static void print(ostream&os,const ::ryoku::edge<T>&e){
        os<<e.from<<" -> "<<e.to<<" (id="<<e.id;
        if constexpr(!is_same_v<T,unweighted>){os<<", cost=";debug::print_value(os,e.cost);}
        os<<')';
    }
};
template<bool Directed,class T>
struct formatter<static_graph<Directed,T>>{
    static void print(ostream&os,const static_graph<Directed,T>&g){
        os<<(Directed?"directed":"undirected")<<" graph [n="<<g.size()<<", m="<<g.edge_size()<<"]\n";
        auto vertices=internal::shown_indices(g.size(),config.max_graph_vertices);
        size_t shown_edges=0;
        for(auto u:vertices){
            if(u==numeric_limits<size_t>::max()){os<<"\n…";continue;}
            os<<'\n'<<u<<(Directed?" ->":" --");
            bool first=true;
            for(const auto&e:g[u]){
                if(shown_edges>=config.max_graph_edges){os<<(first?" ":", ")<<"…";break;}
                os<<(first?" ":", ")<<e.to;first=false;shown_edges++;
                if constexpr(!is_same_v<T,unweighted>){os<<'(';internal::print_value(os,e.cost,0);os<<')';}
            }
        }
    }
};
}
