#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<>
struct formatter<undoable_union_find>{
    static void print(ostream&os,const undoable_union_find&uf){
        auto copy=uf;
        map<int,vector<int>>groups;
        for(int i=0;i<(int)copy.par.size();i++)groups[copy.root(i)].push_back(i);
        os<<"undoable_dsu [n="<<copy.par.size()<<", components="<<groups.size()
          <<", history="<<copy.history.size()<<"]\n";
        size_t id=0;
        for(auto&[_,vertices]:groups){
            if(id==config.max_tree_nodes){os<<"\n…";break;}
            os<<"\n#"<<id++<<' ';internal::print_sequence(os,vertices,0,'{','}');
        }
    }
};
}
