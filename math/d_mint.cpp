#pragma once
#include"barrett.cpp"
#include"barrett.cpp"
template<int id>
struct d_mint{
    using u32=uint32_t;
    using u64=uint64_t;
    u32 val;
    d_mint():val(0){}
    d_mint(ll x){
        int v=x%get_mod();
        if(v<0)v+=get_mod();
        val=v;
    }
    static d_mint raw(int v){
        assert(v>=0);
        d_mint mi;
        mi.val=v;
        return mi;
    }
    d_mint &operator+=(const d_mint&m){
        if((val+=m.val)>=get_mod())val-=get_mod();
        return *this;
    }
    d_mint &operator-=(const d_mint&m){
        if((val+=(get_mod()-m.val))>=get_mod())val-=get_mod();
        return *this;
    }
    d_mint &operator*=(const d_mint&m){
        val=rem(u64(val)*m.val);
        return *this;
    }
    d_mint &operator/=(const d_mint&m){
        val=rem(u64(val)*m.inv().val);
        return *this;
    }
    d_mint operator-() const{
        return d_mint(-val);
    }
    d_mint operator+() const {
        return *this;
    }
    friend d_mint operator+(d_mint lhs, const d_mint& rhs){
        return lhs+=rhs;
    }
    friend d_mint operator-(d_mint lhs, const d_mint& rhs){
        return lhs-=rhs;
    }
    friend d_mint operator*(d_mint lhs, const d_mint& rhs){
        return lhs*=rhs;
    }
    friend d_mint operator/(d_mint lhs,const d_mint&rhs){
        return lhs/=rhs;
    }
    bool operator==(const d_mint&p) const{
        return p.val==val;
    }
    bool operator!=(const d_mint&p) const{
        return p.val!=val;
    }
    d_mint pow(int64_t n) const{
        d_mint res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }

    friend ostream&operator<<(ostream&os,const d_mint&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,d_mint&p){
        int64_t x;
        is>>x;
        p=d_mint(x);
        return is;
    }
    d_mint inv()const{
        int a=val,b=get_mod(),u=1,v=0,t;
        #ifdef LOCAL
        assert(gcd(a,b)==1);
        #endif
        while(b>0){
            t=a/b;
            swap(a-=t*b,b);
            swap(u-=t*v,v);
        }
        return d_mint(u);
    }
    inline static u32 rem(u64 x){return barrett().reduce(x);}
    static inline int &get_mod(){
        static int mod=0;
        return mod;
    }
    static void set_mod(int md){
        assert(0<md&&md<=(1ll<<30)-1);
        get_mod()=md;
        barrett().set(md);
    }
    static inline Barrett&barrett(){
        static Barrett b;
        return b;
    }
};

#include"mod.cpp"