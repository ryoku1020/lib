#pragma once
#include"static-mod-int.hpp"
struct SINT{
    using mint1=StaticModInt<2147483629>;
    using mint2=StaticModInt<2147483647>;
    using ull=unsigned long long;
    static constexpr ull M1=2147483629ULL;
    static constexpr ull M2=2147483647ULL;
    static constexpr ull MOD=M1*M2;
    static constexpr ull INV_M1_MOD_M2=119304647ULL;
    mint1 a;
    mint2 b;
    SINT():a(0),b(0){}
    template<class T>
    SINT(T x):a(x),b(x){}
    static ull modpow(ull a,ull e,ull mod){
        ull r=1;
        while(e){
            if(e&1)r=(__uint128_t)r*a%mod;
            a=(__uint128_t)a*a%mod;
            e>>=1;
        }
        return r;
    }
    ull val()const{
        ull x=a.val;
        ull y=b.val;
        ull t=(y+M2-x)%M2;
        t=(__uint128_t)t*INV_M1_MOD_M2%M2;
        return x+M1*t;
    }

    SINT inv()const{
        assert(a.val!=0&&b.val!=0);
        SINT r;
        r.a=mint1(modpow(a.val,M1-2,M1));
        r.b=mint2(modpow(b.val,M2-2,M2));
        return r;
    }

    SINT& operator+=(const SINT& r){
        a+=r.a,b+=r.b;
        return *this;
    }
    SINT& operator-=(const SINT& r){
        a-=r.a,b-=r.b;
        return *this;
    }
    SINT& operator*=(const SINT& r){
        a*=r.a,b*=r.b;
        return *this;
    }
    SINT& operator/=(const SINT& r){
        return *this*=r.inv();
    }

    SINT operator+()const{return *this;}
    SINT operator-()const{
        SINT r;
        r.a=-a,r.b=-b;
        return r;
    }

    friend SINT operator+(SINT l,const SINT& r){return l+=r;}
    friend SINT operator-(SINT l,const SINT& r){return l-=r;}
    friend SINT operator*(SINT l,const SINT& r){return l*=r;}
    friend SINT operator/(SINT l,const SINT& r){return l/=r;}

    friend bool operator==(const SINT& l,const SINT& r){
        return l.a==r.a&&l.b==r.b;
    }
    friend bool operator!=(const SINT& l,const SINT& r){
        return !(l==r);
    }
    friend bool operator<(const SINT& l,const SINT& r){
        return l.val()<r.val();
    }
    friend bool operator>(const SINT& l,const SINT& r){return r<l;}
    friend bool operator<=(const SINT& l,const SINT& r){return !(r<l);}
    friend bool operator>=(const SINT& l,const SINT& r){return !(l<r);}

    explicit operator ull()const{return val();}

    friend ostream& operator<<(ostream& os,const SINT& x){
        return os<<x.val();
    }
    friend istream& operator>>(istream& is,SINT& x){
        ull v;
        is>>v;
        x=SINT(v);
        return is;
    }
};