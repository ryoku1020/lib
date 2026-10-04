#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<int B>
struct formatter<persistent_union_find<B>>{
    static void print(ostream&os,const persistent_union_find<B>&uf){
        os<<"persistent_dsu n="<<uf.par.n_<<" branching="<<B
          <<" (use debug::version(uf, root) to inspect a version)";
    }
};
template<int B>
struct formatter<version_view<persistent_union_find<B>,typename persistent_union_find<B>::node>>{
    using uf_type=persistent_union_find<B>;
    static void print(ostream&os,const version_view<uf_type,typename uf_type::node>&view){
        auto&uf=view.value;
        map<int,vector<int>>groups;
        for(int i=0;i<uf.par.n_;i++)groups[uf.root(i,view.root)].push_back(i);
        os<<"persistent_dsu [n="<<uf.par.n_<<", components="<<groups.size()<<"]\n";
        size_t id=0;
        for(auto&[_,vertices]:groups){
            if(id==config.max_tree_nodes){os<<"\n…";break;}
            os<<"\n#"<<id++<<' ';internal::print_sequence(os,vertices,0,'{','}');
        }
    }
};
}
