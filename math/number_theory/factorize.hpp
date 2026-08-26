#pragma once

ull mod_mul(ull a,ull b,ull m){
    return ull(static_cast<u128>(a)*b%m);
}
template<class T>
T modpow(T a,T n,T m){
    T res=1%m;a%=m;
    while(n){
        if(n%2)res=res*a%m;
        a=a*a%m;
        n/=2;
    }
    return res;
}
int is_prime(ll n){
    if(n<=1)return 0;
    if(n==2)return 1;
    if(n%2==0)return 0;
    ll k=0,q=n-1;
    while(q%2==0){
        q/=2;
        k++;
    }
    auto judge=[&](vc<ll> base)->int{
        for(auto x:base){
            x%=n;
            if(x==0)continue;
            ll v=modpow<i128>(x,q,n);
            if(v!=1){
                rep(i,k){
                    if(v==n-1)goto end;
                    v=i128(v)*v%n;
                }
                return 0;
            }
            end:;
        }
        return 1;
    };
    if(n<4759123141LL){
        return judge({2,7,61});
    }else{
        return judge({2,325,9375,28178,450775,9780504,1795265022});
    }
}
ll pollard_rho(ll n){
    if(n%2==0)return 2;
    if(n%3==0)return 3;
    static mt19937_64 mt(random_device{}());
    while(1){
        ull y=mt()%(n-1)+1;
        ull c=mt()%(n-1)+1;
        auto f=[&](ull v){
            return (mod_mul(v,v,n)+c)%n;        };
        ull r=1,g=1,x=0,ys=0;
        const ull M=128;
        while(g==1){
            x=y;
            rep(i,r)y=f(y);
            for(ull k=0;k<r&&g==1;k+=M){
                ys=y;
                ull q=1;
                rep(i,min(M,r-k)){
                    y=f(y);
                    ull d=x>y?x-y:y-x;
                    q=mod_mul(q,d,n);
                }
                g=gcd(q,(ull)n);
            }
            r*=2;
        }
        if(g==n){
            do{
                ys=f(ys);
                ull d=x>ys?x-ys:ys-x;
                g=gcd(d,(ull)n);
            }while(g==1);
        }

        if(g!=n)return g;
    }
}
void inner_factorize(ll n,vc<ll>&facts){
    if(n==1)return;
    if(is_prime(n)){
        facts.pb(n);
        return;
    }
    ll d=pollard_rho(n);
    inner_factorize(d,facts);
    inner_factorize(n/d,facts);
}
vc<pair<ll,ll>>factorize(ll n){
    vc<ll> facts;
    inner_factorize(n,facts);
    sort(all(facts));
    vc<pair<ll,ll>> res;
    for(auto p:facts){
        if(res.empty()||res.back().first!=p){
            res.pb({p,1});
        }else{
            res.back().second++;
        }    
    }
    return res;
}

template<class T>
vc<T>divisors(T x){
    auto f=factorize(x);
    vc<T>res;
    auto dfs=[&](auto&dfs,int fr,T v){
        if(fr==f.size()){
            res.pb(v);
            return;
        }
        rep(i,f[fr].second+1){
            dfs(dfs,fr+1,v);
            v*=f[fr].fi;
        }
    };
    dfs(dfs,0,1);
    return res;
}