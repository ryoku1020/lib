#pragma once
#include"base.hpp"
template<class mint>
struct fpsfrac{
    using F=fps<mint>;
    F a,b;
    static bool is_zero(const F&f){
        for(auto x:f)if(x!=0)return false;
        return true;
    }
    fpsfrac():a{0},b{1}{}
    fpsfrac(mint x):a{x},b{1}{}
    fpsfrac(F a):a(move(a)),b{1}{}
    fpsfrac(F a,F b):a(move(a)),b(move(b)){assert(!is_zero(this->b));}

    fpsfrac inv()const{
        assert(!is_zero(a));
        return {b,a};
    }

    fpsfrac operator+()const{return *this;}
    fpsfrac operator-()const{return {-a,b};}

    fpsfrac&operator+=(const fpsfrac&r){
        a=a*r.b+r.a*b;
        b*=r.b;
        return *this;
    }
    fpsfrac&operator-=(const fpsfrac&r){
        a=a*r.b-r.a*b;
        b*=r.b;
        return *this;
    }
    fpsfrac&operator*=(const fpsfrac&r){
        a*=r.a;
        b*=r.b;
        return *this;
    }
    fpsfrac&operator/=(const fpsfrac&r){
        assert(!is_zero(r.a));
        a*=r.b;
        b*=r.a;
        return *this;
    }
    friend fpsfrac operator+(fpsfrac l,const fpsfrac&r){return l+=r;}
    friend fpsfrac operator-(fpsfrac l,const fpsfrac&r){return l-=r;}
    friend fpsfrac operator*(fpsfrac l,const fpsfrac&r){return l*=r;}
    friend fpsfrac operator/(fpsfrac l,const fpsfrac&r){return l/=r;}
    friend bool operator==(const fpsfrac&l,const fpsfrac&r){
        return l.a*r.b==r.a*l.b;
    }
    friend bool operator!=(const fpsfrac&l,const fpsfrac&r){return !(l==r);}
};