#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class X>
struct formatter<potentialized_union_find<X>>{
    static void print(ostream&os,const potentialized_union_find<X>&uf){
        auto copy=uf;
        map<int,vector<pair<int,typename X::value_type>>>groups;
        for(int i=0;i<(int)copy.par.size();i++)groups[copy.root(i)].push_back({i,copy.w[i]});
        os<<"potentialized_dsu [n="<<copy.par.size()<<", components="<<groups.size()<<"]";
        size_t id=0;
        for(auto&[root,vertices]:groups){
            if(id==config.max_tree_nodes){os<<"\n…";break;}
            os<<"\n#"<<id++<<" root="<<root<<' ';internal::print_value(os,vertices,0);
        }
    }
};
}
