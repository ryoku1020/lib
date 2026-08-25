#pragma once
#include "mod.hpp"
struct Mod261Int{
    using u64=uint64_t;
    using u32=uint32_t;
    u64 val;
    static constexpr u64 mod=(1ull<<61)-1;
    static constexpr u64 MASK30=(1UL<<30)-1;
    static constexpr u64 MASK31=(1UL<<31)-1;
    u64 rem(u64 x){
        u64 xu=x>>61;
        u64 xd=x&mod;
        u64 res=xu+xd;
        if(res>=mod)res-=mod;
        return res;
    }
    Mod261Int():val(0){}
    Mod261Int(ll x){
        x%=mod;
        if(x<0)x+=mod;
        val=x;
    }
    static Mod261Int raw(const ll&v){
        assert(v>=0);
        Mod261Int mi;
        mi.val=v;
        return mi;
    }
    Mod261Int&operator+=(const Mod261Int&m){
        if((val+=m.val)>=mod)val-=mod;
        return*this;
    }
    Mod261Int&operator-=(const Mod261Int&m){
        if((val+=(mod-m.val))>=mod)val-=mod;
        return*this;
    }
    Mod261Int&operator*=(const Mod261Int&m){
        u64 au=val>>31,ad=val&MASK31;
        u64 bu=m.val>>31,bd=m.val&MASK31;
        u64 mid=ad*bu+au*bd;
        u64 midu=mid>>30;
        u64 midd=mid&MASK30;
        return*this=Mod261Int::raw(rem(au*bu*2+midu+(midd<<31)+ad*bd));
    }
    Mod261Int&operator/=(const Mod261Int&m){
        return*this*=m.inv();
    }
    Mod261Int operator-()const{
        return Mod261Int(mod-val);
    }
    Mod261Int operator+()const{
        return*this;
    }
    friend Mod261Int operator+(Mod261Int lhs,const Mod261Int&rhs){
        return lhs+=rhs;
    }
    friend Mod261Int operator-(Mod261Int lhs,const Mod261Int&rhs){
        return lhs-=rhs;
    }
    friend Mod261Int operator*(Mod261Int lhs,const Mod261Int&rhs){
        return lhs*=rhs;
    }
    friend Mod261Int operator/(Mod261Int lhs,const Mod261Int&rhs){
        return lhs/=rhs;
    }
    bool operator==(const Mod261Int&p)const{
        return val==p.val;
    }
    bool operator!=(const Mod261Int&p)const{
        return val!=p.val;
    }
    bool operator<(const Mod261Int&p)const{
        return val<p.val;
    }
    bool operator<=(const Mod261Int&p)const{
        return val<=p.val;
    }
    bool operator>(const Mod261Int&p)const{
        return val>p.val;
    }
    bool operator>=(const Mod261Int&p)const{
        return val>=p.val;
    }
    Mod261Int pow(u64 n)const{
        Mod261Int res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }
    Mod261Int inv()const{
        return pow(mod-2);
    }
    friend ostream&operator<<(ostream&os,const Mod261Int&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,Mod261Int&p){
        int64_t x;
        is>>x;
        p=Mod261Int(x);
        return is;
    }
};