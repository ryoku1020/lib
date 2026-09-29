#pragma once
#include "../../template.hpp"
#include "commute.hpp"

template<class info>
struct reversed{
    using value_type=typename info::value_type;
    static constexpr bool commute=famous_has_commute<info>::value;
    static value_type op(const value_type&a,const value_type&b){return info::op(b,a);}
    static value_type id(){return info::id();}
    static value_type e(){return id();}
};
