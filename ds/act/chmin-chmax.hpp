#pragma once
#include "../../template.hpp"
#include "../monoid/min-max.hpp"

template<class T>
struct chmin_min{
    using info=Min<T>;
    using tag=Min<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return min(x,f);}
};
template<class T>
struct chmin_max{
    using info=Max<T>;
    using tag=Min<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return min(x,f);}
};
template<class T>
struct chmax_min{
    using info=Min<T>;
    using tag=Max<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return max(x,f);}
};
template<class T>
struct chmax_max{
    using info=Max<T>;
    using tag=Max<T>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return max(x,f);}
};
