#pragma once
#include"../template.cpp"
#include"mod.cpp"
template<uint32_t mod>
struct s_mint{
    using u32=uint32_t;
    using u64=uint64_t;
    u32 val;
    s_mint():val(0){}
    s_mint(ll x){
        int v=x%mod;
        if(v<0)v+=mod;
        val=v;
    }
    constexpr static uint32_t get_mod(){
        return mod;
    }
    static s_mint raw(int v){
        assert(v>=0);
        s_mint mi;
        mi.val=v;
        return mi;
    }
    s_mint &operator+=(const s_mint&m){
        if((val+=m.val)>=mod)val-=mod;
        return *this;
    }
    s_mint &operator-=(const s_mint&m){
        if((val+=(mod-m.val))>=mod)val-=mod;
        return *this;
    }
    s_mint &operator*=(const s_mint&m){
        val=u64(val)*m.val%mod;
        return *this;
    }
    s_mint &operator/=(const s_mint&m){
        val=u64(val)*m.inv().val%mod;
        return *this;
    }
    s_mint operator-() const{
        return s_mint(mod-val);
    }
    s_mint operator+() const {
        return *this;
    }
    friend s_mint operator+(s_mint lhs, const s_mint& rhs){
        return lhs+=rhs;
    }
    friend s_mint operator-(s_mint lhs, const s_mint& rhs){
        return lhs-=rhs;
    }
    friend s_mint operator*(s_mint lhs, const s_mint& rhs){
        return lhs*=rhs;
    }
    friend s_mint operator/(s_mint lhs,const s_mint&rhs){
        return lhs/=rhs;
    }
    bool operator==(const s_mint&p) const{
        return p.val==val;
    }
    bool operator!=(const s_mint&p) const{
        return p.val!=val;
    }
    s_mint pow(int64_t n) const{
        s_mint res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }

    friend ostream&operator<<(ostream&os,const s_mint&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,s_mint&p){
        int64_t x;
        is>>x;
        p=s_mint(x);
        return is;
    }
    s_mint inv()const{
        int a=val,b=mod,u=1,v=0,t;
        #ifdef LOCAL
        assert(gcd(a,b)==1);
        #endif
        while(b>0){
            t=a/b;
            swap(a-=t*b,b);
            swap(u-=t*v,v);
        }
        return s_mint(u);
    }
};

