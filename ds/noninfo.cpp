#pragma once
#include"../template.cpp"
struct Noninfo{
    using value_type=monostate;
    static value_type op(value_type a,value_type b){return {};}
    static value_type e(){return {};}
    static value_type leaf(){return {};}
};
template<class Info>
struct Nontag{
    using value_type=Info::value_type;
    using lazy_type=monostate;
    static value_type Apply(value_type a,lazy_type b){return {};}
    static lazy_type Merge(lazy_type a,lazy_type b){return {};}
    static lazy_type id(){return {};}
};