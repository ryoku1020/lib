#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class Info,class Tag>
struct formatter<persistent_lazy_segtree<Info,Tag>>{
    static void print(ostream&os,const persistent_lazy_segtree<Info,Tag>&seg){
        os<<"persistent_lazy_segtree n="<<seg.N<<" allocated_nodes="<<seg.ptr-1
          <<" (use debug::version(seg, root) to inspect a version)";
    }
};
template<class Info,class Tag>
struct formatter<version_view<persistent_lazy_segtree<Info,Tag>,int>>{
    using seg_type=persistent_lazy_segtree<Info,Tag>;
    static void print(ostream&os,const version_view<seg_type,int>&view){
        os<<"persistent_lazy_segtree [n="<<view.value.N<<", root="<<view.root<<"]\n\n";
        internal::print_index_values(os,view.value.N,[&](size_t i){return view.value.prod(i,i+1,view.root);});
    }
};
}
