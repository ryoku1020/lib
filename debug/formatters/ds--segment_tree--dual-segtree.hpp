#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class X>
struct formatter<dual_segtree<X>>{
    static void print(ostream&os,const dual_segtree<X>&seg){
        auto copy=seg;
        os<<"dual_segtree [n="<<copy.n<<"]\n\n";
        internal::print_index_values(os,copy.n,[&](size_t i){return copy.get(i);});
    }
};
}
