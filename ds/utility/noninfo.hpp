#pragma once
struct noninfo{
    using value_type=monostate;
    static value_type op(value_type a,value_type b){return {};}
    static value_type e(){return {};}
};
template<class info>
struct nontag{
    using value_type=info::value_type;
    using lazy_type=monostate;
    static value_type apply(value_type a,lazy_type b){return {};}
    static lazy_type merge(lazy_type a,lazy_type b){return {};}
    static lazy_type id(){return {};}
};
