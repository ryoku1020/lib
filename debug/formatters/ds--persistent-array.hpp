#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class T,int B>
struct formatter<persistent_array<T,B>>{
    static void print(ostream&os,const persistent_array<T,B>&array){
        os<<"persistent_array n="<<array.n_<<" branching="<<B<<" span="<<array.b_
          <<" (use debug::version(array, root) to inspect a version)";
    }
};
template<class T,int B>
struct formatter<version_view<persistent_array<T,B>,typename persistent_array<T,B>::Node*>>{
    using array_type=persistent_array<T,B>;
    using view_type=version_view<array_type,typename array_type::Node*>;
    static void print(ostream&os,const view_type&view){
        os<<"persistent_array [n="<<view.value.n_<<"]\n\n";
        internal::print_index_values(os,view.value.n_,[&](size_t i){return view.value.get(i,view.root);});
    }
};
}
