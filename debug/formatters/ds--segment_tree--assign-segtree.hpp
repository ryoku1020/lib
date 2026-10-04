#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class Info>
struct formatter<assign_segtree<Info>>{
    static void print(ostream&os,const assign_segtree<Info>&seg){
        auto copy=seg;
        os<<"assign_segtree [n="<<copy.N<<", assignments="<<copy.ptr<<"]\n\n";
        internal::print_index_values(os,copy.N,[&](size_t i){return copy.prod(i,i+1);});
    }
};
}
