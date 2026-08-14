#pragma once
#include "dynamic-mod-int.hpp"
template<class,class=void>
struct BinomHasGetMod:false_type{};
template<class mint>
struct BinomHasGetMod<mint,void_t<decltype(mint::get_mod())>>:true_type{};
template<class mint>
struct Binom{
private:
    static vector<mint>&fact_table(){static vector<mint>v={1};return v;}
    static vector<mint>&invfact_table(){static vector<mint>v={1};return v;}
    static vector<mint>&invs_table(){static vector<mint>v={0};return v;}
    static int&built_mod(){static int mod=-1;return mod;}
public:
    static void build(int n){
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        auto&_invs=invs_table();
        if constexpr(BinomHasGetMod<mint>::value){
            auto mod=mint::get_mod();
            if(built_mod()!=mod){
                _fact={1};
                _invfact={1};
                _invs={0};
                built_mod()=mod;
            }
        }
        if(n<(int)_fact.size())return;
        int old=_fact.size();
        _fact.resize(n+1);
        _invfact.resize(n+1);
        _invs.resize(n+1);
        if constexpr(BinomHasGetMod<mint>::value){
            auto mod=mint::get_mod();
            for(int i=old;i<=n;i++){
                _fact[i]=_fact[i-1]*i;
                if(i==1)_invs[i]=1;
                else _invs[i]=-_invs[mod%i]*(mod/i);
                _invfact[i]=_invfact[i-1]*_invs[i];
            }
        }else{
            for(int i=old;i<=n;i++){
                _fact[i]=_fact[i-1]*i;
                _invs[i]=mint(1)/i;
                _invfact[i]=_invfact[i-1]*_invs[i];
            }
        }
    }
    static mint fact(int i){
        assert(i>=0);
        build(i);
        return fact_table()[i];
    }
    static mint invfact(int i){
        assert(i>=0);
        build(i);
        return invfact_table()[i];
    }
    static mint inv(int i){
        assert(i>0);
        build(i);
        return invs_table()[i];
    }
    static mint C(int a,int b){//aCb
        if(b==0)return 1;
        if(a<0||b<0||a-b<0)return mint(0);
        build(a);
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        return _fact[a]*_invfact[b]*_invfact[a-b];
    }
    static mint iC(int a,int b){//1/aCb
        if(a<0||b<0||a-b<0)return mint(0);
        build(a);
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        return _fact[b]*_fact[a-b]*_invfact[a];
    }
    static mint P(int a,int b){
        if(a<b||b<0)return 0;
        build(a);
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        return _fact[a]*_invfact[a-b];
    }
    static mint H(int a,int b){
        return C(a+b-1,b);
    }

};
template< typename T >
T extgcd(T a, T b, T &x, T &y) {
  T d = a;
  if(b != 0) {
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  } else {
    x = 1;
    y = 0;
  }
  return d;
}
template<class T>
pair<T,T> inv(T x,T m){
    T a1,a2;
    T res=extgcd<ll>(x,m,a1,a2);
    T md=m/res;
    a1=(a1%md+md)%md;
    return {a1,md};
}
template<class T>
pair<T,T> mod_solve(T a,T b,T m){//return x s.t. ax=b mod m
    a%=m,b%=m;if(a<0)a+=m;if(b<0)b+=m;
    T g=gcd(gcd(a,b),m);
    a/=g,b/=g,m/=g;
    if(gcd(a,m)>1)return {-1,-1};
    return {(inv<ll>(a,m).first*b)%m,inv<ll>(a,m).second};
}

//x^2 ≡ b (mod p)
ll ModSqrt(ll b,ll p){
    static mt19937 mt(random_device{}());
    b%=p;if(b<0)b+=p;
    if(b==0)return 0;
    if(p==2){
        return b;
    }
    assert(p>=3);
    using mint=DynamicModInt<20260801>;mint::set_mod(p);
    if(mint(b).pow((p-1)/2)==-1){
        return -1;
    }
    if(p%4==3){
        return mint(b).pow((p+1)/4).val;
    }
    ll t=[&](){
        ll w;
        while(1){
            ll t=mt()%p;
            w=t*t-b;
            if(mint(w).pow((p-1)/2)==mint(-1)){
                return t;
            }
        }
        assert(0);
    }();
    mint w=mint(t*t-b);
    using T=pair<mint,mint>;
    auto ml=[&](T a,T b)->T{
        return T{a.first*b.first+a.second*b.second*w,a.second*b.first+a.first*b.second};
    };
    ll e=(p+1)/2;
    T ans={1,0};
    T gy={t,1};
    while(e){
        if(e%2)ans=ml(ans,gy);
        gy=ml(gy,gy);
        e/=2;
    }
    return ans.first.val;
}
