#pragma once
struct sieve{
    int n;
    vc<int>mf;
    sieve(int n):n(n),mf(n+1){
        build();
    }
    void build(){
        rep(i,n+1)mf[i]=i;
        for(int i=2;i<=n/i;i++)if(mf[i]==i){
            for(int j=i*i;j<=n;j+=i)chmin(mf[j],i);
        }
    }
    vc<pair<int,int>>factorize(int x){
        assert(0<x&&x<=n);
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
    vc<int>div(int x){
        assert(0<x&&x<=n);
        vc<int>res{1};
        for(auto [p,e]:factorize(x)){
            int sz=res.size(),pw=1;
            rep(i,e){
                pw*=p;
                rep(j,sz)res.pb(res[j]*pw);
            }
        }
        sort(all(res));
        return res;
    }
    int mobius(int x){
        assert(0<x&&x<=n);
        auto pf=factorize(x);
        for(auto [p,e]:pf)if(e>1)return 0;
        return pf.size()%2?-1:1;
    }
    bool is_prime(int x){
        assert(0<=x&&x<=n);
        return x>=2&&mf[x]==x;
    }
    int phi(int x){
        assert(0<x&&x<=n);
        int res=x;
        while(x>1){
            int p=mf[x];
            res=res/p*(p-1);
            while(x%p==0)x/=p;
        }
        return res;
    }
};