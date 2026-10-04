#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class T,auto Op,int Extra>
struct formatter<base_disjoint_set_union<T,Op,Extra>>{
    static void print(ostream&os,const base_disjoint_set_union<T,Op,Extra>&uf){
        auto copy=uf;
        map<int,vector<int>>groups;
        for(int i=0;i<(int)copy.par.size();i++)groups[copy.root(i)].push_back(i);
        os<<"dsu [n="<<copy.par.size()<<", components="<<groups.size()<<"]\n";
        size_t shown=0;
        for(auto&[root,vertices]:groups){
            if(shown==config.max_tree_nodes){os<<"\n…";break;}
            os<<"\n#"<<shown++<<' ';
            internal::print_sequence(os,vertices,0,'{','}');
            if constexpr(Extra){os<<" data=";internal::print_value(os,copy.data[root],0);}
        }
    }
};
}
