#pragma once
#include "../../template.hpp"
#include "../monoid/sum-prod.hpp"
#include "../monoid/assign-affine.hpp"

template<class T>
struct mul_sum{
    using info=Sum<T>;
    using tag=Prod<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return x*f;}
};
template<class T>
struct affine_sum{
    using info=Sum<T>;
    using tag=affine<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll len){return x*f.fi+f.se*len;}
};
