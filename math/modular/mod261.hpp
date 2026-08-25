#pragma once
struct mod261_int{
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
    mod261_int():val(0){}
    mod261_int(ll x){
        x%=mod;
        if(x<0)x+=mod;
        val=x;
    }
    static mod261_int raw(const ll&v){
        assert(v>=0);
        mod261_int mi;
        mi.val=v;
        return mi;
    }
    mod261_int&operator+=(const mod261_int&m){
        if((val+=m.val)>=mod)val-=mod;
        return*this;
    }
    mod261_int&operator-=(const mod261_int&m){
        if((val+=(mod-m.val))>=mod)val-=mod;
        return*this;
    }
    mod261_int&operator*=(const mod261_int&m){
        u64 au=val>>31,ad=val&MASK31;
        u64 bu=m.val>>31,bd=m.val&MASK31;
        u64 mid=ad*bu+au*bd;
        u64 midu=mid>>30;
        u64 midd=mid&MASK30;
        return*this=mod261_int::raw(rem(au*bu*2+midu+(midd<<31)+ad*bd));
    }
    mod261_int&operator/=(const mod261_int&m){
        return*this*=m.inv();
    }
    mod261_int operator-()const{
        return mod261_int(mod-val);
    }
    mod261_int operator+()const{
        return*this;
    }
    friend mod261_int operator+(mod261_int lhs,const mod261_int&rhs){
        return lhs+=rhs;
    }
    friend mod261_int operator-(mod261_int lhs,const mod261_int&rhs){
        return lhs-=rhs;
    }
    friend mod261_int operator*(mod261_int lhs,const mod261_int&rhs){
        return lhs*=rhs;
    }
    friend mod261_int operator/(mod261_int lhs,const mod261_int&rhs){
        return lhs/=rhs;
    }
    bool operator==(const mod261_int&p)const{
        return val==p.val;
    }
    bool operator!=(const mod261_int&p)const{
        return val!=p.val;
    }
    bool operator<(const mod261_int&p)const{
        return val<p.val;
    }
    bool operator<=(const mod261_int&p)const{
        return val<=p.val;
    }
    bool operator>(const mod261_int&p)const{
        return val>p.val;
    }
    bool operator>=(const mod261_int&p)const{
        return val>=p.val;
    }
    mod261_int pow(u64 n)const{
        mod261_int res(1),mul(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }
    mod261_int inv()const{
        return pow(mod-2);
    }
    friend ostream&operator<<(ostream&os,const mod261_int&p){
        os<<p.val;
        return os;
    }
    friend istream&operator>>(istream&is,mod261_int&p){
        int64_t x;
        is>>x;
        p=mod261_int(x);
        return is;
    }
};
