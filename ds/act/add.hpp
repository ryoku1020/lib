#pragma once
#include "../../template.hpp"
#include "../monoid/min-max.hpp"
#include "../monoid/sum-prod.hpp"

template<class T>
struct add_min{
    using info=Min<T>;
    using tag=Sum<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return x+f;}
};
template<class T>
struct add_max{
    using info=Max<T>;
    using tag=Sum<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return x+f;}
};
template<class T>
struct add_sum{
    using info=Sum<T>;
    using tag=Sum<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll len){return x+f*len;}
};
