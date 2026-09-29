#pragma once
#include "../../template.hpp"

template<class T>
struct Gcd{
    using value_type=T;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){return gcd(a,b);}
    static value_type id(){return T(0);}
    static value_type e(){return id();}
};
template<class T>
struct Lcm{
    using value_type=T;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){return lcm(a,b);}
    static value_type id(){return T(1);}
    static value_type e(){return id();}
};
