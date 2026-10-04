#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<>
struct formatter<bit_vector>{
    static void print(ostream&os,const bit_vector&bv){
        os<<"bit_vector [n="<<bv.n<<"]\n\n";
        internal::print_bits(os,bv.n,[&](size_t i){return bv.rank1(i,i+1);});
    }
};
}
