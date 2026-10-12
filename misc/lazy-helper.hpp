#pragma once
namespace ryoku{
template<class T> struct lambda_args;
template<class C,class R,class... Args>
struct lambda_args<R(C::*)(Args...) const>{
    using type=tuple<decay_t<Args>...>;
};
template<class C,class R,class... Args>
struct lambda_args<R(C::*)(Args...)>:lambda_args<R(C::*)(Args...) const>{};

template<class F>
struct lazy_helper{
    using T=typename lambda_args<decltype(&F::operator())>::type;
    F f;
    vector<T> qs;
    lazy_helper(F f):f(move(f)){}
    template<class... Args>
    void query(Args&&... args){
        qs.emplace_back(forward<Args>(args)...);
    }
    void set(){
        for(auto& x:qs)apply(f,x);
        qs.clear();
    }
    void clear(){qs.clear();}
};
}