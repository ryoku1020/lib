#pragma once
#include "barrett.hpp"
#include "barrett.hpp"
template<int id>
struct DynamicModInt{
    using u32=uint32_t;
    using u64=uint64_t;
    u32 val;
    DynamicModInt():val(0){}
    DynamicModInt(ll x){
        int v=x%get_mod();
        if(v<0)v+=get_mod();
        val=v;
    }
    static DynamicModInt raw(int v){
        assert(v>=0);
        DynamicModInt mi;
        mi.val=v;
        return mi;
    }
    DynamicModInt &operator+=(const DynamicModInt&m){
        if((val+=m.val)>=get_mod())val-=get_mod();
        return *this;
    }
    DynamicModInt &operator-=(const DynamicModInt&m){
        if((val+=(get_mod()-m.val))>=get_mod())val-=get_mod();
        return *this;
    }
    DynamicModInt &operator*=(const DynamicModInt&m){
        val=rem(u64(val)*m.val);
        return *this;
    }
    DynamicModInt &operator/=(const DynamicModInt&m){
        val=rem(u64(val)*m.inv().val);
        return *this;
    }
    DynamicModInt operator-() const{
        return DynamicModInt(val?get_mod()-val:0);
    }
    DynamicModInt operator+() const {
        return *this;
    }
    friend DynamicModInt operator+(DynamicModInt lhs, const DynamicModInt& rhs){
        return lhs+=rhs;
    }
    friend DynamicModInt operator-(DynamicModInt lhs, const DynamicModInt& rhs){
        return lhs-=rhs;
    }
    friend DynamicModInt operator*(DynamicModInt lhs, const DynamicModInt& rhs){
        return lhs*=rhs;
    }
    friend DynamicModInt operator/(DynamicModInt lhs,const DynamicModInt&rhs){
        return lhs/=rhs;
    }
    bool operator==(const DynamicModInt&p) const{
        return p.val==val;
    }
    bool operator!=(const DynamicModInt&p) const{
        return p.val!=val;
    }
    DynamicModInt pow(int64_t n) const{
        DynamicModInt res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }

    friend ostream&operator<<(ostream&os,const DynamicModInt&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,DynamicModInt&p){
        int64_t x;
        is>>x;
        p=DynamicModInt(x);
        return is;
    }
    DynamicModInt inv()const{
        int a=val,b=get_mod(),u=1,v=0,t;
        #ifdef LOCAL
        assert(gcd(a,b)==1);
        #endif
        while(b>0){
            t=a/b;
            swap(a-=t*b,b);
            swap(u-=t*v,v);
        }
        return DynamicModInt(u);
    }
    inline static u32 rem(u64 x){return BarrettReduction().reduce(x);}
    static inline int &get_mod(){
        static int mod=0;
        return mod;
    }
    static void set_mod(int md){
        assert(0<md&&md<=(1ll<<30)-1);
        get_mod()=md;
        BarrettReduction().set(md);
    }
    static inline Barrett&BarrettReduction(){
        static Barrett b;
        return b;
    }
};

#include "mod.hpp"
