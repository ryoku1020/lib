#pragma once
#include "../../template.hpp"

namespace ryoku{
template<class T>
struct Mprod{
    using value_type=T;
    static constexpr bool commute=false;
    static value_type op(value_type a,value_type b){return a*b;}
    static value_type id(){return T::unit();}
    static value_type e(){return id();}
};

}
