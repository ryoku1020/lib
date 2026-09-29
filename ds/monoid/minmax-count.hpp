#pragma once
#include "../../template.hpp"

template<class T,T INF=inf<T>>
struct MinCount{
    using value_type=pair<T,int>;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){
        if(a.fi<b.fi)return a;
        if(b.fi<a.fi)return b;
        return {a.fi,a.se+b.se};
    }
    static value_type id(){return {INF,0};}
    static value_type e(){return id();}
    static value_type make(T x){return {x,1};}
};
template<class T,T NEG_INF=neg_inf<T>>
struct MaxCount{
    using value_type=pair<T,int>;
    static constexpr bool commute=true;
    static value_type op(value_type a,value_type b){
        if(a.fi>b.fi)return a;
        if(b.fi>a.fi)return b;
        return {a.fi,a.se+b.se};
    }
    static value_type id(){return {NEG_INF,0};}
    static value_type e(){return id();}
    static value_type make(T x){return {x,1};}
};
