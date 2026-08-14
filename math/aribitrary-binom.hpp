#pragma once
#include"../lib/math/barrett.hpp"
struct ArbitraryBinom{
    ArbitraryBinom(){}
    ArbitraryBinom(ll m){build(m);}
    struct BINOM{
        ll p,e,q;
        vc<ll>fact,ppow,inv;
        int neg;
        Barrett bar;
        ll mul(ll a,ll b){
            return bar.reduce((uint64_t)a*b);
        }
        ll extgcd(ll a,ll b,ll&x,ll&y){
            if(b==0){
                x=1;y=0;
                return a;
            }
            ll X,Y;
            ll g=extgcd(b,a%b,X,Y);
            x=Y;
            y=X-a/b*Y;
            return g;
        }
        ll mod_inv(ll a,ll mod){
            ll x,y;
            ll g=extgcd(a,mod,x,y);
            assert(g==1);
            x%=mod;
            if(x<0)x+=mod;
            return x;
        }
        void build(ll p_,ll e_){
            p=p_;e=e_;
            ppow.resize(e+1,1);rep(i,e)ppow[i+1]=ppow[i]*p;
            q=ppow.back();
            assert(q<=INT_MAX);
            bar.set(q);
            fact.resize(q);inv.resize(q);
            fact[0]=1;
            REP(i,1,q)fact[i]=mul(fact[i-1],(i%p?i:1));
            ll cur=mod_inv(fact[q-1],q);
            for(ll i=q-1;i>=1;i--){
                if(i%p)inv[i]=mul(cur,fact[i-1]);
                cur=mul(cur,(i%p?i:1));
            }
            neg=(fact[q-1]==q-1);
        }
        pair<ll,ll>calc(ll n){
            ll f=1,v=0;
            while(n){
                if(neg&&((n/q)&1))f=q-f;
                f=mul(f,fact[n%q]);
                n/=p;
                v+=n;
            }
            return {f,v};
        }
        ll query(ll a,ll b){
            if(b==0)return 1;
            if(a<0||b<0||a-b<0)return 0;
            auto[A,va]=calc(a);
            auto[B,vb]=calc(b);
            auto[C,vc]=calc(a-b);
            ll v=va-vb-vc;
            if(v>=e)return 0;
            return mul(mul(A,mul(inv[B],inv[C])),ppow[v]);
        }
    };
    ll mod;
    vc<array<ll,3>>ms;
    vc<BINOM>bs;
    vc<ll>crtcoef;
    ll extgcd(ll a,ll b,ll&x,ll&y){
        if(b==0){
            x=1;y=0;
            return a;
        }
        ll X,Y;
        ll g=extgcd(b,a%b,X,Y);
        x=Y;
        y=X-a/b*Y;
        return g;
    }
    ll mod_inv(ll a,ll m){
        ll x,y;
        ll g=extgcd(a,m,x,y);
        assert(g==1);
        x%=m;
        if(x<0)x+=m;
        return x;
    }
    void build(ll m){
        mod=m;
        for(ll i=2;i*i<=m;i++){
            ll cnt=0;while(m%i==0)cnt++,m/=i;
            if(cnt)ms.pb({i,cnt,POW<ll>(i,cnt)});
        }
        if(m>1)ms.pb({m,1,m});
        rep(i,ms.size()){
            bs.pb({});
            bs.back().build(ms[i][0],ms[i][1]);
        }
        crtcoef.resize(ms.size());
        rep(i,ms.size()){
            ll q=ms[i][2],M=mod/q;
            crtcoef[i]=(i128)M*mod_inv(M%q,q)%mod;
        }
    }
    ll query(ll a,ll b){
        if(mod==1)return 0;
        if(b==0)return 1;
        if(a<0||b<0||a-b<0)return 0;
        if(ms.size()==1)return bs[0].query(a,b);
        ll ans=0;
        rep(i,ms.size())ans=(ans+(i128)bs[i].query(a,b)*crtcoef[i])%mod;
        return ans;
    }
};