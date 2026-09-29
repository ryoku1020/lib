#pragma once
#include "../../template.hpp"

template<class T,T INF=inf<T>>
struct Min{
    using value_type=T;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){return min(a,b);}
    static value_type id(){return INF;}
    static value_type e(){return id();}
};
template<class T,T NEG_INF=neg_inf<T>>
struct Max{
    using value_type=T;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){return max(a,b);}
    static value_type id(){return NEG_INF;}
    static value_type e(){return id();}
};
