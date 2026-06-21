#pragma once
#include "mod.hpp"
template<uint32_t mod>
struct StaticModInt{
    static_assert(0<mod&&mod<=(1u<<31)-1);
    using u32=uint32_t;
    using u64=uint64_t;
    u32 val;
    StaticModInt():val(0){}
    StaticModInt(ll x){
        ll v=x%mod;
        if(v<0)v+=mod;
        val=v;
    }
    constexpr static uint32_t get_mod(){
        return mod;
    }
    static StaticModInt raw(int v){
        assert(v>=0);
        StaticModInt mi;
        mi.val=v;
        return mi;
    }
    StaticModInt &operator+=(const StaticModInt&m){
        if((val+=m.val)>=mod)val-=mod;
        return *this;
    }
    StaticModInt &operator-=(const StaticModInt&m){
        if((val+=(mod-m.val))>=mod)val-=mod;
        return *this;
    }
    StaticModInt &operator*=(const StaticModInt&m){
        val=u64(val)*m.val%mod;
        return *this;
    }
    StaticModInt &operator/=(const StaticModInt&m){
        val=u64(val)*m.inv().val%mod;
        return *this;
    }
    StaticModInt operator-() const{
        return StaticModInt(mod-val);
    }
    StaticModInt operator+() const {
        return *this;
    }
    friend StaticModInt operator+(StaticModInt lhs, const StaticModInt& rhs){
        return lhs+=rhs;
    }
    friend StaticModInt operator-(StaticModInt lhs, const StaticModInt& rhs){
        return lhs-=rhs;
    }
    friend StaticModInt operator*(StaticModInt lhs, const StaticModInt& rhs){
        return lhs*=rhs;
    }
    friend StaticModInt operator/(StaticModInt lhs,const StaticModInt&rhs){
        return lhs/=rhs;
    }
    bool operator==(const StaticModInt&p) const{
        return p.val==val;
    }
    bool operator!=(const StaticModInt&p) const{
        return p.val!=val;
    }
    StaticModInt pow(int64_t n) const{
        StaticModInt res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }

    friend ostream&operator<<(ostream&os,const StaticModInt&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,StaticModInt&p){
        int64_t x;
        is>>x;
        p=StaticModInt(x);
        return is;
    }
    StaticModInt inv()const{
        int64_t a=val,b=mod,u=1,v=0,t;
        #ifdef LOCAL
        assert(gcd(a,b)==1);
        #endif
        while(b>0){
            t=a/b;
            swap(a-=t*b,b);
            swap(u-=t*v,v);
        }
        return StaticModInt(u);
    }
};
