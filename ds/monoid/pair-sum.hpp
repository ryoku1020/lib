#pragma once
#include "../../template.hpp"

template<class T>
struct PairSum{
    using value_type=pair<T,T>;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){return {a.fi+b.fi,a.se+b.se};}
    static value_type id(){return {T(0),T(0)};}
    static value_type e(){return id();}
};
