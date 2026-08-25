#pragma once
template<uint32_t mod>
struct static_modint{
    static_assert(0<mod&&mod<=(1u<<31)-1);
    using u32=uint32_t;
    using u64=uint64_t;
    u32 val;
    static_modint():val(0){}
    static_modint(ll x){
        ll v=x%mod;
        if(v<0)v+=mod;
        val=v;
    }
    constexpr static uint32_t get_mod(){
        return mod;
    }
    static static_modint raw(int v){
        assert(v>=0);
        static_modint mi;
        mi.val=v;
        return mi;
    }
    static_modint &operator+=(const static_modint&m){
        if((val+=m.val)>=mod)val-=mod;
        return *this;
    }
    static_modint &operator-=(const static_modint&m){
        if((val+=(mod-m.val))>=mod)val-=mod;
        return *this;
    }
    static_modint &operator*=(const static_modint&m){
        val=u64(val)*m.val%mod;
        return *this;
    }
    static_modint &operator/=(const static_modint&m){
        val=u64(val)*m.inv().val%mod;
        return *this;
    }
    static_modint operator-() const{
        return static_modint(mod-val);
    }
    static_modint operator+() const {
        return *this;
    }
    friend static_modint operator+(static_modint lhs, const static_modint& rhs){
        return lhs+=rhs;
    }
    friend static_modint operator-(static_modint lhs, const static_modint& rhs){
        return lhs-=rhs;
    }
    friend static_modint operator*(static_modint lhs, const static_modint& rhs){
        return lhs*=rhs;
    }
    friend static_modint operator/(static_modint lhs,const static_modint&rhs){
        return lhs/=rhs;
    }
    bool operator==(const static_modint&p) const{
        return p.val==val;
    }
    bool operator!=(const static_modint&p) const{
        return p.val!=val;
    }
    static_modint pow(int64_t n) const{
        static_modint res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }

    friend ostream&operator<<(ostream&os,const static_modint&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,static_modint&p){
        int64_t x;
        is>>x;
        p=static_modint(x);
        return is;
    }
    static_modint inv()const{
        int64_t a=val,b=mod,u=1,v=0,t;
        #ifdef LOCAL
        assert(gcd(a,b)==1);
        #endif
        while(b>0){
            t=a/b;
            swap(a-=t*b,b);
            swap(u-=t*v,v);
        }
        return static_modint(u);
    }
};
