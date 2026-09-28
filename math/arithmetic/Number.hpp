#pragma once
struct sieve{
    inline static int n=1;
    inline static vc<int>mf={0,1};
    inline static vc<int>mobius_;
    sieve(){}
    sieve(int N){build(N);}
    static void build(int N){
        if(N<=n)return;
        n=N;
        mf.resize(n+1);
        rep(i,n+1)mf[i]=i;
        for(int i=2;i<=n/i;i++)if(mf[i]==i){
            for(int j=i*i;j<=n;j+=i)chmin(mf[j],i);
        }
        mobius_.clear();
    }

    static vc<pair<int,int>>factorize(int x){
        assert(0<x);
        if(x>n)build(x);
        vc<pair<int,int>>res;
        while(x>1){
            int p=mf[x];
            res.pb({p,0});
            while(x%p==0){
                x/=p;
                res.back().second++;
            }
        }
        return res;
    }
    struct divisor_view{
        struct factor{
            int p,e,pe;
        };
        vc<factor>f;
        int sz=1;
        divisor_view(int x){
            for(auto[p,e]:factorize(x)){
                int pe=1;
                rep(_,e)pe*=p;
                f.pb({p,e,pe});
                sz*=e+1;
            }
        }
        struct iterator{
            const vc<factor>*f;
            vc<int>cnt;
            int x=1,id=0,sz;
            int operator*()const{return x;}
            iterator&operator++(){
                id++;
                if(id==sz)return *this;
                rep(i,f->size()){
                    auto [p,e,pe]=(*f)[i];
                    if(cnt[i]<e){
                        cnt[i]++;
                        x*=p;
                        break;
                    }
                    cnt[i]=0;
                    x/=pe;
                }
                return *this;
            }
            bool operator!=(const iterator&r)const{
                return id!=r.id;
            }
        };
        iterator begin()const{
            return {&f,vc<int>(f.size()),1,0,sz};
        }
        iterator end()const{
            return {&f,{},0,sz,sz};
        }
    };
    static divisor_view div(int x){
        assert(0<x);
        return divisor_view(x);
    }
    static void mobd(){
        mobius_.resize(n+1);
        mobius_[1]=1;
        REP(i,2,n+1){
            ll p=mf[i];
            if(i%(p*p)==0)mobius_[i]=0;
            else mobius_[i]=-mobius_[i/p];
        }
    }
    static vc<int>nom0div(int x){
        auto fp=factorize(x);
        vc<int>res(1<<fp.size());
        rep(i,1<<fp.size()){
            int push=1;
            rep(j,fp.size()){
                if(i>>j&1)push*=fp[j].fi;
            }
            res[i]=push;
        }
        return res;
    }
    static int mobius(int x){
        assert(0<x);
        if(x>n)build(x);
        if(mobius_.empty())mobd();
        return mobius_[x];
    }
    static bool is_prime(int x){
        assert(0<=x);
        if(x<2)return false;
        if(x>n)build(x);
        return mf[x]==x;
    }
    static int phi(int x){
        assert(0<x);
        if(x>n)build(x);
        int res=x;
        while(x>1){
            int p=mf[x];
            res=res/p*(p-1);
            while(x%p==0)x/=p;
        }
        return res;
    }
};