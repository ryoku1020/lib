#pragma once
#include"../template.cpp"
#include"d_mint.cpp"
template<class mint>
struct Binom{
    inline static vector<mint>fact={1},invfact={1};
    static void build(int n){
        if(n<(int)fact.size())return;
        fact=invfact=vector<mint>(n+1);
        fact[0]=1;
        for(int i=1;i<=n;i++)fact[i]=fact[i-1]*i;
        invfact[n]=(1/fact[n]);
        for(int i=n-1;i>=0;i--)invfact[i]=invfact[i+1]*(i+1);
    }
    static mint C(int a,int b){//aCb
        if(a<0||b<0||a-b<0)return mint(0);
        while((int)fact.size()<=a){
            fact.push_back(fact.back()*(fact.size()));
        }
        while((int)invfact.size()<=a){
            invfact.push_back(invfact.back()/invfact.size());
        }
        return fact[a]*invfact[b]*invfact[a-b];
    }
    static mint P(int a,int b){
        if(a<b||b<0)return 0;
        return fact[a]*invfact[a-b];
    }
    static mint H(int a,int b){
        return C(a+b-1,b);
    }  
};
template<class T>
pair<T,T> inv(T x,T m){
    T a1,a2;
    T res=extgcd(x,m,a1,a2);
    return {a1,m/res};
}
template<class T>
pair<T,T> mod_solve(T a,T b,T m){//return x s.t. ax=b mod m
    a%=m,b%=m;if(a<0)a+=m;if(b<0)b+=m;
    T g=gcd(gcd(a,b),m);
    a/=g,b/=g,m/=g;
    if(gcd(a,m)>1)return {-1,-1};
    return {(inv(a,m).first*b)%m,inv(a,m).second};
}
//https://nyaannyaan.github.io/library/modulo/mod-sqrt.hpp.html
int64_t mod_sqrt(const int64_t &a, const int64_t &p) {
  assert(0 <= a && a < p);
  if (a < 2) return a;
  using Mint = d_mint<409075245>;
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