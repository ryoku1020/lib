#pragma once
#include "barrett.hpp"
template<int id>
struct dynamic_modint{
    using u32=uint32_t;
    using u64=uint64_t;
    u32 val;
    dynamic_modint():val(0){}
    dynamic_modint(ll x){
        ll v=x%get_mod();
        if(v<0)v+=get_mod();
        val=v;
    }
    static dynamic_modint raw(int v){
        assert(v>=0);
        dynamic_modint mi;
        mi.val=v;
        return mi;
    }
    dynamic_modint &operator+=(const dynamic_modint&m){
        if((val+=m.val)>=get_mod())val-=get_mod();
        return *this;
    }
    dynamic_modint &operator-=(const dynamic_modint&m){
        if((val+=(get_mod()-m.val))>=get_mod())val-=get_mod();
        return *this;
    }
    dynamic_modint &operator*=(const dynamic_modint&m){
        val=rem(u64(val)*m.val);
        return *this;
    }
    dynamic_modint &operator/=(const dynamic_modint&m){
        val=rem(u64(val)*m.inv().val);
        return *this;
    }
    dynamic_modint operator-() const{
        return dynamic_modint(val?get_mod()-val:0);
    }
    dynamic_modint operator+() const {
        return *this;
    }
    friend dynamic_modint operator+(dynamic_modint lhs, const dynamic_modint& rhs){
        return lhs+=rhs;
    }
    friend dynamic_modint operator-(dynamic_modint lhs, const dynamic_modint& rhs){
        return lhs-=rhs;
    }
    friend dynamic_modint operator*(dynamic_modint lhs, const dynamic_modint& rhs){
        return lhs*=rhs;
    }
    friend dynamic_modint operator/(dynamic_modint lhs,const dynamic_modint&rhs){
        return lhs/=rhs;
    }
    bool operator==(const dynamic_modint&p) const{
        return p.val==val;
    }
    bool operator!=(const dynamic_modint&p) const{
        return p.val!=val;
    }
    dynamic_modint pow(int64_t n) const{
        dynamic_modint res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }

    friend ostream&operator<<(ostream&os,const dynamic_modint&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,dynamic_modint&p){
        int64_t x;
        is>>x;
        p=dynamic_modint(x);
        return is;
    }
    dynamic_modint inv()const{
        int64_t a=val,b=get_mod(),u=1,v=0,t;
        #ifdef LOCAL
        assert(gcd(a,b)==1);
        #endif
        while(b>0){
            t=a/b;
            swap(a-=t*b,b);
            swap(u-=t*v,v);
        }
        return dynamic_modint(u);
    }
    inline static u32 rem(u64 x){return barrett_reduction().reduce(x);}
    static inline int &get_mod(){
        static int mod=0;
        return mod;
    }
    static void set_mod(int md){
        assert(0<md&&md<=(1ll<<31)-1);
        get_mod()=md;
        barrett_reduction().set(md);
    }
    static inline barrett&barrett_reduction(){
        static barrett b;
        return b;
    }
};

