#pragma once
#include"../template.cpp"
template<class Value_type>
struct Min{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return min(a,b);
    }
    static value_type e(){
        return numeric_limits<value_type>::max();
    }
    static value_type leaf(){
        return numeric_limits<value_type>::max();
    }
};
template<class Value_type>
struct Max{
    using value_type=Value_type;
    static value_type op(value_type a,value_type b){
        return max(a,b);
    }
    static value_type e(){
        return numeric_limits<value_type>::min();
    }
    static value_type leaf(){
        return numeric_limits<value_type>::min();
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
};
template<class Value_type>
struct ArgMin{
    using value_type=pair<Value_type,int>;
    static value_type op(value_type a,value_type b){
        return min(a,b);
    }
    static value_type e(){
        return {numeric_limits<Value_type>::max(),-1};
    }
    static value_type leaf(){
        return {numeric_limits<Value_type>::max(),-1};
    }
};
template<class Value_type>
struct ArgMax{
    using value_type=pair<Value_type,int>;
    static value_type op(value_type a,value_type b){
        return max(a,b);
    }
    static value_type e(){
        return {numeric_limits<Value_type>::min(),-1};
    }
    static value_type leaf(){
        return {numeric_limits<Value_type>::min(),-1};
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
};