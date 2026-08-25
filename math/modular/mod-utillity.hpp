
#pragma once
#include"dynamic-mod-int.hpp"

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
ll mod_sqrt(ll b,ll p){
    static mt19937 mt(random_device{}());
    b%=p;if(b<0)b+=p;
    if(b==0)return 0;
    if(p==2){
        return b;
    }
    assert(p>=3);
    using mint=dynamic_modint<20260801>;mint::set_mod(p);
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
