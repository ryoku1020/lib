#pragma once
#include"multi-discrete.hpp"
#include"../../math/rand.hpp"
#include"../arithmetic/Number.hpp"
#include"dynamic-modint64.hpp"
vc<ll>findlog(ll p,ll g,vc<ll>a){
    if(p<5e6)return multidiscrete(p,g,a);
    using mint1=dynamic_modint64<202608271>;
    using mint2=dynamic_modint64<202608272>;
    mint1::set_mod(p);
    const int B0=50;
    const int prepare=1<<19;
    randf rn;
    mint1 mg=mint1::raw(g);
    vc<pair<ll,ll>>regs;
    regs.reserve(prepare+1024);
    rep(i,prepare){
        ll r=rn(0,p-1);
        regs.pb({r,mg.pow(r).val});
    }
    ll R=isqrt((p-1)/2);
    sieve sieve(R+1);
    vc<int>lpf(R+1);
    lpf[1]=1;
    REP(x,2,R+1){
        int q=sieve.mf[x];
        lpf[x]=max(q,lpf[x/q]);
    }
    vc<ll>base;
    REP(i,2,B0)if(sieve.is_prime(i))base.pb(i);
    auto ls=multidiscrete(p,g,base);
    mint2::set_mod(p-1);
    vc<mint2>logprime(R+1);
    rep(i,base.size())logprime[base[i]]=ls[i];
    auto getsmalllog=[&](ll x){
        mint2 res=0;
        while(x>1){
            int q=sieve.mf[x];
            res+=logprime[q];
            x/=q;
        }
        return res;
    };
    auto findfrac=[&](ll T,int lim)->pair<ll,ll>{
        auto good=[&](ll x){
            return 0<x&&x<=R&&lpf[x]<lim;
        };
        if(good(T))return {T,1};
        ll r0=p,r1=T;
        ll v0=0,v1=1;
        bool neg=1;
        while(r1){
            ll q=r0/r1;
            ll r2=r0-q*r1;
            i128 vv=(i128)q*v1+v0;
            if(vv>R)break;
            ll v2=vv;
            if(good(r2)&&good(v2))return {neg?-r2:r2,v2};
            r0=r1;
            r1=r2;
            v0=v1;
            v1=v2;
            neg^=1;
        }
        return {0,-1};
    };
    auto getlog=[&](ll x,int lim)->ll{
        for(ll id=0;;id++){
            if(id==(ll)regs.size()){
                ll r=rn(0,p-1);
                regs.pb({r,mg.pow(r).val});
            }
            auto [u,v]=findfrac((mint1::raw(x)*mint1::raw(regs[id].second)).val,lim);
            if(v==-1)continue;
            mint2 res=getsmalllog(u<0?-u:u)-getsmalllog(v)-regs[id].first;
            if(u<0)res+=(p-1)/2;
            return res.val;
        }
    };
    REP(q,B0,R+1){
        if(!sieve.is_prime(q))continue;
        logprime[q]=getlog(q,q);
    }
    vc<ll>res(a.size());
    rep(i,a.size())res[i]=getlog(a[i],R+1);
    return res;
}
