#pragma once
#include "../template.hpp"
template<class T=ll,bool reduce_always=true>
struct Frac{
    using compare_type=conditional_t<(sizeof(T)<=8),i128,T>;
    T a,b;
    void fix_sign(){
        if(b<0){
            a=-a;
            b=-b;
        }
    }
    constexpr Frac():a(0),b(1){}
    constexpr Frac(T a_):a(a_),b(1){}
    constexpr Frac(T a_,T b_):a(a_),b(b_){
        assert(b!=0);
        if constexpr(reduce_always)reduce();
        else fix_sign();
    }
    void reduce(){
        assert(b!=0);
        T g=gcd(a,b);
        if(g!=0){
            a/=g;
            b/=g;
        }
        fix_sign();
    }
    Frac inv()const{
        assert(a!=0);
        return Frac(b,a);
    }
    ld val()const{
        return (ld)a/b;
    }
    Frac &operator+=(const Frac&f){
        if constexpr(reduce_always){
            T g=gcd(b,f.b);
            a=a*(f.b/g)+f.a*(b/g);
            b=b/g*f.b;
        }else{
            a=a*f.b+f.a*b;
            b*=f.b;
        }
        if constexpr(reduce_always)reduce();
        else fix_sign();
        return *this;
    }
    Frac &operator-=(const Frac&f){
        if constexpr(reduce_always){
            T g=gcd(b,f.b);
            a=a*(f.b/g)-f.a*(b/g);
            b=b/g*f.b;
        }else{
            a=a*f.b-f.a*b;
            b*=f.b;
        }
        if constexpr(reduce_always)reduce();
        else fix_sign();
        return *this;
    }
    Frac &operator*=(const Frac&f){
        if constexpr(reduce_always){
            T g1=gcd(a,f.b),g2=gcd(f.a,b);
            a=a/g1*(f.a/g2);
            b=b/g2*(f.b/g1);
        }else{
            a*=f.a;
            b*=f.b;
        }
        if constexpr(reduce_always)reduce();
        else fix_sign();
        return *this;
    }
    Frac &operator/=(const Frac&f){
        assert(f.a!=0);
        if constexpr(reduce_always){
            T g1=gcd(a,f.a),g2=gcd(f.b,b);
            a=a/g1*(f.b/g2);
            b=b/g2*(f.a/g1);
        }else{
            a*=f.b;
            b*=f.a;
        }
        if constexpr(reduce_always)reduce();
        else fix_sign();
        return *this;
    }
    Frac operator-() const{
        return Frac(-a,b);
    }
    Frac operator+() const {
        return *this;
    }
    friend Frac operator+(Frac lhs, const Frac& rhs){
        return lhs+=rhs;
    }
    friend Frac operator-(Frac lhs, const Frac& rhs){
        return lhs-=rhs;
    }
    friend Frac operator*(Frac lhs, const Frac& rhs){
        return lhs*=rhs;
    }
    friend Frac operator/(Frac lhs,const Frac&rhs){
        return lhs/=rhs;
    }
    friend bool operator==(const Frac&l,const Frac&r){
        return compare_type(l.a)*r.b==compare_type(r.a)*l.b;
    }
    friend bool operator!=(const Frac&l,const Frac&r){
        return !(l==r);
    }
    friend bool operator<(const Frac&l,const Frac&r){
        return compare_type(l.a)*r.b<compare_type(r.a)*l.b;
    }
    friend bool operator>(const Frac&l,const Frac&r){
        return r<l;
    }
    friend bool operator<=(const Frac&l,const Frac&r){
        return !(r<l);
    }
    friend bool operator>=(const Frac&l,const Frac&r){
        return !(l<r);
    }
    #ifdef LOCAL
    friend ostream&operator<<(ostream&os,const Frac&f){
        os<<f.a<<"/"<<f.b;
        return os;
    }
    #endif
};
template<class Frac>
Frac abs(Frac a){
    if(a<0)return -a;
    return a;
}