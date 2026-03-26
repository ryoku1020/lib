#pragma once
#include"../template.cpp"


struct fastset{
    using u64=uint64_t;
    static inline constexpr int B=64;
    int n;
    vc<vc<u64>>val;
    int N;
    int size;
    //fastset for val in [0,n) 
    fastset():n(0),N(0),size(0){}
    fastset(int n_):size(0){
        n=n_;
        N=B;
        vc<u64>raw(1);
        val.pb(raw);
        while(N<n){
            raw.resize(raw.size()*B);
            val.pb(raw);
            N*=B;
        }
    }
    array<int,5>dig(int x){
        array<int,5>res{};
        rep(i,5){
            res[i]=x%B;
            x/=B;
        }
        return res;
    }
    int insert(int x){
        auto xdig=dig(x);
        int idx=0;
        rep(i,(int)val.size()-1){
            val[i][idx]|=1ull<<(xdig[val.size()-i-1]);
            idx=idx*B+(xdig[val.size()-i-1]);
        }
        int res=0;
        if(~val.back()[idx]>>(x%B)&1)size++,res=1;
        val.back()[idx]|=1ull<<(x%B);
        return res;
    }
    int erase(int x){
        auto xdig=dig(x);
        vc<int>Ihis(val.size());
        int idx=0;
        int X=x;
        rep(i,(int)val.size()-1){
            Ihis[i]=idx;
            idx=idx*B+(xdig[val.size()-i-1]);
        }
        int res=0;
        if(val.back()[idx]>>(X%B)&1)size--,res=1;
        val.back()[idx]&=~(1ull<<(X%B));
        int no=!!val.back()[idx];
        drep(i,val.size()-1){
            auto&idx=Ihis[i];
            if(no==0){
                val[i][idx]&=~(1ull<<(xdig[val.size()-i-1]));
            }
            no=!!val[i][idx];
        }
        return res;
    }
    int next(int x){
        chmax(x,0);
        if(x>=n)return n;
        if(val.back()[x/B]>>(x%B)&1)return x;
        auto xdig=dig(x);
        vc<int>Ihis(val.size());
        int idx=0;
        rep(i,(int)val.size()){
            Ihis[i]=idx;
            idx=idx*B+(xdig[val.size()-i-1]);
        }
        int hi=-1;
        drep(i,val.size()){
            if(lbit(val[i][Ihis[i]],xdig[val.size()-i-1]+1)!=-1){
                hi=i+1;
                idx=Ihis[i]*B+lbit(val[i][Ihis[i]],xdig[val.size()-i-1]+1);
                break;
            }
        }
        if(hi==-1)return n;
        REP(i,hi,val.size()){
            idx=idx*B+lbit(val[i][idx]);
        }
        return idx;
    }
    int prev(int x){
        if(x<0)return -1;
        chmin(x,n-1);
        if(val.back()[x/B]>>(x%B)&1)return x;
        auto xdig=dig(x);
        vc<int>Ihis(val.size());
        int idx=0;
        rep(i,(int)val.size()){
            Ihis[i]=idx;
            idx=idx*B+(xdig[val.size()-i-1]);
        }
        int hi=-1;
        drep(i,val.size()){
            if(tbit(val[i][Ihis[i]],xdig[val.size()-i-1]-1)!=-1){
                hi=i+1;
                idx=Ihis[i]*B+tbit(val[i][Ihis[i]],xdig[val.size()-i-1]-1);
                break;
            }
            
        }
        if(hi==-1)return -1;
        REP(i,hi,val.size()){
            idx=idx*B+tbit(val[i][idx]);
        }
        return idx;
    }
    int count(int x){
        if(x<0||x>=n)return 0;
        if(val.back()[x/B]>>(x%B)&1)return 1;
        return 0;
    }
};