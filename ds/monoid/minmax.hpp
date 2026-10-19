#pragma once
#include "../../template.hpp"

namespace ryoku{
template<class T>
struct MinMax{
    using value_type=pair<T,T>;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){
        return {min(a.fi,b.fi),max(a.se,b.se)};
    }
    static value_type id(){return {inf<T>,-inf<T>};}
    static value_type e(){return id();}
};

}
