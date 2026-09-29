#pragma once
#include "../../template.hpp"
#include "../monoid/min-max.hpp"
#include "../monoid/sum-prod.hpp"
#include "../monoid/assign-affine.hpp"

template<class T>
struct assign_min{
    using info=Min<T>;
    using tag=assign<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,const lazy_type&f,ll){return f?*f:x;}
};
template<class T>
struct assign_max{
    using info=Max<T>;
    using tag=assign<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,const lazy_type&f,ll){return f?*f:x;}
};
template<class T>
struct assign_sum{
    using info=Sum<T>;
    using tag=assign<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,const lazy_type&f,ll len){return f?*f*len:x;}
};
