#pragma once
#include "../../template.hpp"

template<class T>
struct Sum{
    using value_type=T;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){return a+b;}
    static value_type id(){return T(0);}
    static value_type e(){return id();}
};
template<class T>
struct Prod{
    using value_type=T;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){return a*b;}
    static value_type id(){return T(1);}
    static value_type e(){return id();}
};
