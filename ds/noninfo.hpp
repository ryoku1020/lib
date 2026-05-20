#pragma once
struct Noninfo{
    using value_type=monostate;
    static value_type op(value_type a,value_type b){return {};}
    static value_type e(){return {};}
    static value_type leaf(){return {};}
    static value_type get2(auto a){return {};}
};
template<class Info>
struct Nontag{
    using value_type=Info::value_type;
    using lazy_type=monostate;
    static value_type Apply(value_type a,lazy_type b){return {};}
    static lazy_type Merge(lazy_type a,lazy_type b){return {};}
    static lazy_type id(){return {};}
};