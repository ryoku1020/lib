#pragma once
#include"../template.hpp"
vc<ll>floors(ll n){
    vc<ll>res;
    ll last=1;
    for(ll i=1;i*i<=n;i++){
        if(res.empty()||res.back()!=n/i){
            res.push_back(n/i);
            last=n/i;
        }
    }
    DREP(i,last-1,1){
        ll L=n/(i+1)+1,R=n/(i);
        if(L<=R)res.push_back(i);
    }
    reverse(all(res));
    return res;
}
template<class T,class F,class G>
tuple<vc<T>,vc<int>,vc<ll>>lucy_dp(ll n,F f,G g){
    auto QN=floors(n);
    vc<T>dp(QN.size()); 
    rep(i,QN.size())dp[i]=f(QN[i]);
    vc<ll>prime_count(QN.size());
    rep(i,QN.size())prime_count[i]=QN[i]-1;
    int m_val=sqrtl(n);
    vector<int>id1(m_val+1),id2(m_val+1);
    for(int i=0;i<QN.size();++i){
        if(QN[i]<=m_val)id1[QN[i]]=i;
        else id2[n/QN[i]]=i;
    }
    auto get_idx=[&](ll x){return x<=m_val?id1[x]:id2[n/x];};
    vc<int>primes;
    for(ll x=2;x*x<=n;x++){
        if(prime_count[get_idx(x)]>prime_count[get_idx(x-1)]){
            primes.pb(x);
            for(int i=(int)QN.size()-1;i>=0;--i){
                auto&v=QN[i];
                if(x*x>v)break;
                dp[i]-=(dp[get_idx(v/x)]-dp[get_idx(x-1)])*g(x);
                prime_count[i]-=prime_count[get_idx(v/x)]-prime_count[get_idx(x-1)];
            }
        }
    }
    return {dp,primes,QN};
}
template<class DP,class F,class G,class H,class mint>
mint black_algorithm(ll n,F f,G g,H h){
    auto [dp,primes,floors]=lucy_dp<DP,F,G>(n,f,g);
    int m_val=sqrtl(n);
    vector<int>id1(m_val+1),id2(m_val+1);
    for(int i=0;i<floors.size();++i){
        if(floors[i]<=m_val)id1[floors[i]]=i;
        else id2[n/floors[i]]=i;
    }
    auto get_idx=[&](ll x){return x<=m_val?id1[x]:id2[n/x];};
    mint ans=1;
    auto dfs=[&](auto&dfs,ll now,int prime_idx,mint coef,mint coefpre,int cum)->void{
        mint sub=(now==1?mint(0):mint(dp[get_idx(primes[prime_idx])]));
        ans+=coef*(mint(dp[get_idx(n/now)])-sub);
        REP(i,prime_idx,primes.size()){
            ll p=primes[i];
            if(i==prime_idx){
                ll next_now=now*p;
                if(next_now<=n){
                    mint next_coef=coefpre*h(p,cum+1);
                    if(now!=1)ans+=next_coef;
                    if(n/next_now>=p)dfs(dfs,next_now,i,next_coef,coefpre,cum+1);
                }
            }else{
                if(n/now<p*p)break;
                dfs(dfs,now*p,i,coef*h(p,1),coef,1);
            }
        }
    };
    dfs(dfs,1,0,1,1,0);
    return ans;
}
/*
mint A,B; 
struct Data{
    mint cnt,sum;
    Data operator+(const Data&o)const{return{cnt+o.cnt,sum+o.sum};}
    Data operator-(const Data&o)const{return{cnt-o.cnt,sum-o.sum};}
    Data&operator-=(const Data&o){cnt-=o.cnt;sum-=o.sum;return*this;}
    Data operator*(ll x)const{return{cnt,sum*mint(x)};}
    operator mint()const{return A*cnt+B*sum;} 
};*/