#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class T>
struct formatter<binary_indexed_tree<T>>{
    static void print(ostream&os,const binary_indexed_tree<T>&bit){
        vector<T>values;
        for(int i=0;i<bit.n;i++)values.push_back(bit.sum(i,i+1));
        os<<"fenwick_tree n="<<bit.n<<"\nvalues = ";
        internal::print_value(os,values,0);
        os<<"\nbit    = ";internal::print_value(os,bit.data,0);
    }
};
}
