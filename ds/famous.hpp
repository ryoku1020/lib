#pragma once
#include "../template.hpp"
template<class Value_type,Value_type inf>
struct Min{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return min(a,b);
    }
    static value_type e(){
        return inf;
    }
    static value_type leaf(){
        return inf;
    }
    static value_type get(auto a){
        return inf;
    }
};
template<class Value_type,Value_type neg_inf>
struct Max{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return max(a,b);
    }
    static value_type e(){
        return neg_inf;
    }
    static value_type leaf(){
        return neg_inf;
    }
    static value_type get2(auto a){
        return neg_inf;
    }
};
template<class Value_type>
struct Sum{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return a+b;
    }
    static value_type e(){
        return 0;
    }
    static value_type leaf(){
        return 0;
    }
    static value_type get2(auto a){
        return 0;
    }
};
template<class Value_type>
struct Prod{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return a*b;
    }
    static value_type e(){
        return 1;
    }
    static value_type leaf(){
        return 1;
    }
    static value_type get2(auto a){
        return 1;
    }
};
template<class... Infos>
struct Merger{
    using value_type=tuple<typename Infos::value_type...>;
    template<size_t... I>
    static value_type op_impl(value_type a,value_type b,index_sequence<I...>){
        return value_type{Infos::op(get<I>(a),get<I>(b))...};
    }
    static value_type op(value_type a,value_type b){
        return op_impl(a,b,index_sequence_for<Infos...>{});
    }
    static value_type e(){
        return value_type{Infos::e()...};
    }
    static value_type leaf(){
        return value_type{Infos::leaf()...};
    }
    static value_type get2(auto a){
        return value_type{Infos::get2(a)...};
    }
};
template<class Value_type>
struct Affine{
    using value_type=pair<Value_type,Value_type>;
    static value_type op(value_type a,value_type b){
        return {a.first*b.first,a.second*b.first+b.second};
    }
    static value_type e(){
        return {1,0};
    }
    static value_type leaf(){
        return e();
    }
    static value_type get2(auto a){
        return e();
    }
};
template<class Info>
struct Reversed{
    using value_type=Info::value_type;
    static value_type op(value_type a,value_type b){
        return Info::op(b,a);
    }
    static value_type e(){
        return Info::e();
    }
    static value_type leaf(){
        return Info::leaf();
    }
    static value_type get2(){
        return Info::get2();
    }
};