#pragma once
#include "../../template.hpp"
#include "../monoid/pair-sum.hpp"

template<class T>
struct range_linear_range_sum{
    using info=PairSum<T>;
    using tag=PairSum<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll len){return {x.fi+f.fi*x.se+f.se*len,x.se};}
    static value_type make(ll i,T x){return {x,T(i)};}
    static lazy_type make_tag(ll l,T a,T b){return {a,b-a*l};}
};
