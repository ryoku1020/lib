#pragma once
#include "../../template.hpp"

template<class T,class=void>
struct famous_has_commute{
    static constexpr bool value=false;
};
template<class T>
struct famous_has_commute<T,decltype((void)T::commute,void())>{
    static constexpr bool value=T::commute;
};
