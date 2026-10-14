#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class T,int N,int M>
struct formatter<fixed_matrix<T,N,M>>{
    static void print(ostream&os,const fixed_matrix<T,N,M>&mt){
        if(!N){os<<"[0 × "<<M<<']';return;}
        internal::print_matrix(os,mt.a,0);
    }
};
}
