#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class T>
struct formatter<matrix<T>>{
    static void print(ostream&os,const matrix<T>&mt){
        if(!mt.n){os<<"[0 × "<<mt.m<<']';return;}
        internal::print_matrix(os,mt.a,0);
    }
};
}
