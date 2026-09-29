#pragma once
#include "../../template.hpp"
#include "../monoid/extreme-k.hpp"
#include "../monoid/sum-prod.hpp"

template<class Key,class Val,int K,Val NEG_INF=neg_inf<Val>>
struct add_maxk{
    using info=maxk_info<Key,Val,K,NEG_INF>;
    using tag=Sum<Val>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return x+=f;}
};
template<class Key,class Val,int K,Val INF=inf<Val>>
struct add_mink{
    using info=mink_info<Key,Val,K,INF>;
    using tag=Sum<Val>;
    using value_type=typename info::value_type;
    using lazy_type=typename tag::value_type;
    static value_type act(value_type x,lazy_type f,ll){return x+=f;}
};
