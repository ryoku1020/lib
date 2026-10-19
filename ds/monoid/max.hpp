#pragma once
#include "../../template.hpp"

namespace ryoku{
template<class T,T NEG_INF=neg_inf<T>>
struct Max{
    using value_type=T;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){return max(a,b);}
    static value_type id(){return NEG_INF;}
    static value_type e(){return id();}
};

}
