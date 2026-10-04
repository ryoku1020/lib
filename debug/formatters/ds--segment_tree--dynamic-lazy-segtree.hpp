#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class acted,class Size>
struct formatter<dynamic_lazy_segtree<acted,Size>>{
    static void print(ostream&os,const dynamic_lazy_segtree<acted,Size>&seg){
        os<<"dynamic_lazy_segtree size="<<seg.N<<" allocated_nodes="<<seg.pool.size()<<" root="<<seg.root;
        if(seg.root){
            os<<"\nroot value=";internal::print_value(os,seg.root->val,0);
            os<<" lazy=";internal::print_value(os,seg.root->lazy,0);
        }
    }
};
}
