#pragma once
#include"base.hpp"
template<class mint>using spfs=vc<pair<int,mint>>;
template<class mint>
fps<mint>InvSparse(int n,spfs<mint>sp){
    if(n==0)return{};
    mint iv;
    fps<mint>res(n);
    rep(i,sp.size()){
        if(sp[i].first==0){
            iv=1/sp[i].second;
            res[0]=iv;
            sp.erase(sp.begin()+i);
            break;
        }
    }
    assert(iv.val);
    REP(i,1,n){
        for(auto&x:sp){
            if(x.first<=i){
                res[i]-=res[i-x.first]*x.second;
            }
        }
        res[i]=res[i]*iv;
    }
    return res;
}
template<class mint>
fps<mint>LogSparse(int n,spfs<mint>sp){
    if(n==0)return{};
    fps<mint>ds=InvSparse(n-1,sp);
    fps<mint>nds(n-1);
    rep(i,sp.size()){
        if(sp[i].first==0)continue;
        rep(j,ds.size()){
            if(j+sp[i].first-1<n-1){
                nds[j+sp[i].first-1]+=ds[j]*sp[i].second*(sp[i].first);
            }
        }
    }
    ds=move(nds);
    ds.insert(ds.begin(),0);
    REP(i,1,ds.size())ds[i]*=Binom<mint>::inv(i);
    return ds;
}
template<class mint>
fps<mint>ExpSparse(int n,spfs<mint>sp){

    if(n==0)return {};
    fps<mint>f(n);f[0]=1;
    rep(i,n-1){
        mint ri=0;
        rep(j,sp.size()){
            if(i-(sp[j].first-1)>=0){
                ri+=sp[j].second*f[i-(sp[j].first-1)]*sp[j].first;
            }
        }
        f[i+1]=ri*Binom<mint>::inv(i+1);
    }   
    return f;
}
template<class mint>
fps<mint>PowSparse(int n,spfs<mint>sp,ll m){
    if(n==0)return {};
    if(m==0){
        fps<mint>res(n);res[0]=1;
        return res;
    }
    if(sp.size()==0){
        return fps<mint>(n);
    }
    pii V{inf<int>,inf<int>};rep(i,sp.size())chmin(V,pii{sp[i].first,i});
    int i=V.second;
    mint sp0=1/sp[i].second;
    if(sp[i].first){
        if((i128)sp[i].first*m>=n){
            return fps<mint>(n);
        }
        auto nsp=sp;for(auto&x:nsp)x.first-=sp[i].first;
        auto res=PowSparse(n-sp[i].first*m,nsp,m);
        vc<mint>zero(sp[i].first*m);
        zero.insert(zero.end(),res.begin(),res.end());
        return zero;
    }
    vc<mint>F(n);F[0]=mint(sp[i].second).pow(m);
    rep(j,n-1){
        mint gj=0;
        for(auto&x:sp){
            if(x.first){
                if(j-x.first+1>=0)
                gj-=x.second*F[j-x.first+1]*(j-x.first+1),
                gj+=m*F[j-x.first+1]*x.first*x.second;
            }
        }   
        F[j+1]=gj*Binom<mint>::inv(j+1)*sp0;
    }
    return F;
}
template<class mint>
optional<fps<mint>>SqrtSparse(int n,spfs<mint>sp){
    if(sp.empty())return fps<mint>(n);
    int mini=[&](){
        int i;
        pii v{inf<int>,inf<int>};
        rep(j,sp.size())chmin(v,pii{sp[j].first,j});
        return v.second;
    }();
    int mindeg=sp[mini].first;
    if(mindeg%2)return nullopt;
    if(mindeg){
        for(auto&x:sp){
            x.first-=mindeg;
        }
        auto res=SqrtSparse(n-mindeg/2,sp);if(!res.has_value())return nullopt;
        vc<mint>zero(mindeg/2);
        zero.insert(zero.end(),res.value().begin(),res.value().end());
        return zero;
    }
    if(sp[mini].second!=1){
        ll coef=ModSqrt(sp[mini].second.val,mint::get_mod());
        if(coef==-1)return nullopt;
        mint v=1/sp[mini].second;for(auto&x:sp)x.second*=v;
        auto res=SqrtSparse(n,sp);if(!res.has_value())return nullopt;
        res.value()*=(mint)coef;
        return res;
    }
    mint inv2=1/mint(2);
    fps<mint>F(n);F[0]=1;
    rep(i,n-1){
        mint sm=0;
        for(auto&[d,v]:sp){
            if(d&&i-(d-1)>=0){
                sm+=v*F[i-(d-1)]*d;
                sm-=2*v*F[(i-d)+1]*(i-d+1);
            }
        }
        sm*=inv2;
        F[i+1]=sm*Binom<mint>::inv(i+1);
    }
    return F;
}