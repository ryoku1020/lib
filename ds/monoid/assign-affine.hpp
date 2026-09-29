#pragma once
#include "../../template.hpp"

template<class T>
struct assign{
    using value_type=optional<T>;
    static value_type op(const value_type&old_tag,const value_type&new_tag){return new_tag?new_tag:old_tag;}
    static value_type id(){return nullopt;}
    static value_type e(){return id();}
};
template<class T>
struct affine{
    using value_type=pair<T,T>;
    static value_type op(value_type old_tag,value_type new_tag){return {new_tag.fi*old_tag.fi,new_tag.fi*old_tag.se+new_tag.se};}
    static value_type id(){return {T(1),T(0)};}
    static value_type e(){return id();}
};
