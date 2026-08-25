template<int N>
struct ninfo{
    array<int,N>mf_;
    bool built_=0;

    void buildp(){
        if(built_)return;
        built_=1;
        REP(i,1,N)mf_[i]=i;
        REP(i,2,N){
            if(mf_[i]==i&&i*i<N)for(int j=i*i;j<N;j+=i){
                chmin(mf_[j],i);
            }
        }
    }
    vc<pair<int,int>>factorize(int n){
        assert(0<n&&n<N);
        buildp();
        vc<pair<int,int>>res;
        while(n>1){
            int tar=mf_[n];
            res.pb({tar,0});
            while(n%tar==0){
                n/=tar;
                res.back().second++;
            }
        }
        return res;
    }
    vc<int>div(int n){
        vc<int>res{1};
        for(auto [p,e]:factorize(n)){
            int sz=res.size(),pw=1;
            rep(i,e){
                pw*=p;
                rep(j,sz)res.pb(res[j]*pw);
            }
        }
        sort(all(res));
        return res;
    }
    int mobius(int n){
        auto pf=factorize(n);
        for(auto [p,e]:pf)if(e>1)return 0;
        return pf.size()%2?-1:1;
    }
    bool is_prime(int n){
        assert(0<=n&&n<N);
        buildp();
        return n>=2&&mf_[n]==n;
    }
    int phi(int n){
        ll res=n;
        while(n>1){
            res*=mf_[n]-1;
            res/=mf_[n];
            int M=mf_[n];
            while(n%M==0)n/=M;
        }
        return res;
    }
};
