#pragma once
template<int id>
struct dynamic_modint64{
    using u64=uint64_t;
    using i128=__int128_t;
    using u128=__uint128_t;
    u64 val;
    dynamic_modint64():val(0){}
    dynamic_modint64(i128 x){
        i128 v=(i128)x%get_mod();
        if(v<0)v+=get_mod();
        val=v;
    }
    static dynamic_modint64 raw(u64 v){
        assert(v<get_mod());
        dynamic_modint64 mi;
        mi.val=v;
        return mi;
    }
    dynamic_modint64&operator+=(const dynamic_modint64&m){
        u64 md=get_mod(),x=val+m.val-md;
        val=x+(md&-(x>>63));
        return *this;
    }
    dynamic_modint64&operator-=(const dynamic_modint64&m){
        u64 md=get_mod(),x=val-m.val;
        val=x+(md&-(x>>63));
        return *this;
    }
    dynamic_modint64&operator*=(const dynamic_modint64&m){
        val=rem(u128(val)*m.val);
        return *this;
    }
    dynamic_modint64&operator/=(const dynamic_modint64&m){
        val=rem(u128(val)*m.inv().val);
        return *this;
    }

    dynamic_modint64 operator-()const{return raw(val?get_mod()-val:0);}
    dynamic_modint64 operator+()const{return *this;}

    friend dynamic_modint64 operator+(dynamic_modint64 lhs,const dynamic_modint64&rhs){return lhs+=rhs;}
    friend dynamic_modint64 operator-(dynamic_modint64 lhs,const dynamic_modint64&rhs){return lhs-=rhs;}
    friend dynamic_modint64 operator*(dynamic_modint64 lhs,const dynamic_modint64&rhs){return lhs*=rhs;}
    friend dynamic_modint64 operator/(dynamic_modint64 lhs,const dynamic_modint64&rhs){return lhs/=rhs;}

    bool operator==(const dynamic_modint64&p)const{return p.val==val;}
    bool operator!=(const dynamic_modint64&p)const{return p.val!=val;}

    dynamic_modint64 pow(int64_t n)const{
        dynamic_modint64 res(1),mul=raw(val);
        while(n){
            if(n%2)res*=mul;
            mul*=mul;
            n/=2;
        }
        return res;
    }
    friend ostream&operator<<(ostream&os,const dynamic_modint64&p){return os<<p.val;}
    friend istream&operator>>(istream&is,dynamic_modint64&p){
        int64_t x;
        is>>x;
        return p=dynamic_modint64(x),is;
    }
    dynamic_modint64 inv()const{
        i128 a=val,b=get_mod(),u=1,v=0,t;
#ifdef LOCAL
        assert(gcd(val,get_mod())==1);
#endif
        while(b){
            t=a/b;
            swap(a-=t*b,b);
            swap(u-=t*v,v);
        }
        u%=get_mod();
        if(u<0)u+=get_mod();
        return raw((u64)u);
    }
    static inline u64 rem(u128 x){return x%get_mod();}
    static inline u64&get_mod(){
        static u64 mod=1;
        return mod;
    }
    static void set_mod(u64 md){
        assert(0<md&&md<=1e18);
        get_mod()=md;
    }
};