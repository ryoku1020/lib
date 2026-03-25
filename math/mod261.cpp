#pragma once
#include"mod.cpp"
#include"../template.cpp"
struct mod261{
    using u64=uint64_t;
    using u32=uint32_t;
    u64 val;
    static constexpr u64 mod=(1ull<<61)-1;
    static constexpr u64 MASK30 = (1UL << 30) - 1;
    static constexpr u64 MASK31 = (1UL << 31) - 1;
    u64 rem(u64 x){
        u64 xu=x>>61;
        u64 xd=x&mod;
        u64 res=xu+xd;
        if (res>=mod)res-=mod;
        return res;
    }
    mod261():val(0){}
    mod261(ll x){
        x%=mod;
        if(x<0)x+=mod;
        val=x;
    }
    static mod261 raw(const ll& v){
        assert(v>=0);
        mod261 mi;
        mi.val=v;
        return mi;
    }
    mod261 &operator+=(const mod261&m){
        if((val+=m.val)>=mod)val-=mod;
        return *this;
    }
    mod261 &operator-=(const mod261&m){
        if((val+=(mod-m.val))>=mod)val-=mod;
        return *this;
    }
    mod261 &operator*=(const mod261&m){
        u64 au=val>>31,ad=val&MASK31;
        u64 bu=m.val>>31,bd=m.val&MASK31;
        u64 mid=ad*bu+au*bd;
        u64 midu=mid>>30;
        u64 midd=mid&MASK30;
        return *this=mod261::raw(rem(au*bu*2+midu+(midd<<31)+ad*bd));
    }
    mod261 &operator/=(const mod261&m){
        return *this*=m.inv();
    }
    mod261 operator-() const{
        return mod261(mod-val);
    }
    mod261 operator+() const {
        return *this;
    }
    friend mod261 operator+(mod261 lhs, const mod261& rhs){
        return lhs+=rhs;
    }
    friend mod261 operator-(mod261 lhs, const mod261& rhs){
        return lhs-=rhs;
    }
    friend mod261 operator*(mod261 lhs, const mod261& rhs){
        return lhs*=rhs;
    }
    friend mod261 operator/(mod261 lhs,const mod261&rhs){
        return lhs/=rhs;
    }
    bool operator==(const mod261&p) const{
        return p.val==val;
    }
    bool operator!=(const mod261&p) const{
        return p.val!=val;
    }
    mod261 pow(u64 n) const{
        mod261 res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }
    mod261 inv()const{
        return pow(mod-2);
    }
    friend ostream&operator<<(ostream&os,const mod261&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,mod261&p){
        int64_t x;
        is>>x;
        p=mod261(x);
        return is;
    }
};