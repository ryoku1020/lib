#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class T,int D>
struct formatter<wm_base<T,D>>{
    static void print(ostream&os,const wm_base<T,D>&wm){
        os<<"wavelet_matrix n="<<wm.n<<" levels="<<D<<"\nvalues = ";
        internal::print_value(os,wm.gi,0);
        for(int level=D-1;level>=0;level--){
            os<<"\nlevel "<<level<<" mid="<<wm.mid[level]<<" : ";
            size_t n=min<size_t>(wm.n,config.max_sequence_elements);
            for(size_t i=0;i<n;i++)os<<(wm.bv[level].rank1(i,i+1)?'1':'0');
            if(n<(size_t)wm.n)os<<"…";
        }
    }
};
}
