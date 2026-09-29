#pragma once
#include "../../template.hpp"
#include "commute.hpp"

template<class... Infos>
struct merger{
    using value_type=tuple<typename Infos::value_type...>;
    static constexpr bool commute=(famous_has_commute<Infos>::value&&...);
    template<size_t...I>
    static value_type op_impl(const value_type&a,const value_type&b,index_sequence<I...>){return {Infos::op(get<I>(a),get<I>(b))...};}
    static value_type op(const value_type&a,const value_type&b){return op_impl(a,b,index_sequence_for<Infos...>{});}
    static value_type id(){return {Infos::id()...};}
    static value_type e(){return id();}
};
