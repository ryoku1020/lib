#pragma once
#include "dynamic-mod-int.hpp"
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
        auto mod=mint::get_mod();
        if(built_mod()!=mod){
            _fact={1};
            _invfact={1};
            _invs={0};
            built_mod()=mod;
        }
        if(n<(int)_fact.size())return;
        int old=_fact.size();
        _fact.resize(n+1);
        _invfact.resize(n+1);
        _invs.resize(n+1);
        for(int i=old;i<=n;i++){
            _fact[i]=_fact[i-1]*i;
            if(i==1)_invs[i]=1;
            else _invs[i]=-_invs[mod%i]*(mod/i);
            _invfact[i]=_invfact[i-1]*_invs[i];
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
        if(a<0||b<0||a-b<0)return mint(0);
        build(a);
        auto&_fact=fact_table();
        auto&_invfact=invfact_table();
        return _fact[a]*_invfact[b]*_invfact[a-b];
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
    return {a1,m/res};
}
template<class T>
pair<T,T> mod_solve(T a,T b,T m){//return x s.t. ax=b mod m
    a%=m,b%=m;if(a<0)a+=m;if(b<0)b+=m;
    T g=gcd(gcd(a,b),m);
    a/=g,b/=g,m/=g;
    if(gcd(a,m)>1)return {-1,-1};
    return {(inv<ll>(a,m).first*b)%m,inv<ll>(a,m).second};
}
//https://nyaannyaan.github.io/library/modulo/mod-sqrt.hpp.html
int64_t mod_sqrt(const int64_t &a, const int64_t &p) {
  assert(0 <= a && a < p);
  if (a < 2) return a;
  using Mint = DynamicModInt<409075245>;
  Mint::set_mod(p);
  if (Mint(a).pow((p - 1) >> 1) != 1) return -1;
  Mint b = 1, one = 1;
  while (b.pow((p - 1) >> 1) == 1) b += one;
  int64_t m = p - 1, e = 0;
  while (m % 2 == 0) m >>= 1, e += 1;
  Mint x = Mint(a).pow((m - 1) >> 1);
  Mint y = Mint(a) * x * x;
  x *= a;
  Mint z = Mint(b).pow(m);
  while (y != 1) {
    int64_t j = 0;
    Mint t = y;
    while (t != one) {
      j += 1;
      t *= t;
    }
    z = z.pow(int64_t(1) << (e - j - 1));
    x *= z;
    z *= z;
    y *= z;
    e = j;
  }
  return x.val;
}
