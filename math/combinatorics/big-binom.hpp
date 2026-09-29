#pragma once
#include"../modular/binom.hpp"
template<class mint>
struct big_binom{
    struct agg_stack{
        vc<mint>a,prod;
        void push(mint x){
            a.pb(x);
            prod.pb((prod.empty()?mint(1):prod.back())*x);
        }
        void pop(){
            assert(a.size());
            a.pop_back();
            prod.pop_back();
        }
        mint get()const{
            return prod.empty()?mint(1):prod.back();
        }
        int size()const{return a.size();}
        bool empty()const{return a.empty();}
        void clear(){a.clear();prod.clear();}
    };
    ll n;
    int k;
    mint ifact;
    agg_stack l,r;
    big_binom(ll n,int k):n(n),k(k),ifact(1){
        assert(0<=k);
        REP(i,1,k+1)ifact*=binom<mint>::inv(i);
        REP(i,0,k)r.push(mint(n-k+1+i));
    }
    void rebuild(){
        vc<mint>v;
        v.reserve(l.size()+r.size());
        drep(i,l.a.size())v.pb(l.a[i]);
        for(auto x:r.a)v.pb(x);
        l.clear();r.clear();
        int m=v.size()/2;
        for(int i=m-1;i>=0;i--)l.push(v[i]);
        REP(i,m,v.size())r.push(v[i]);
    }
    void push_front(mint x){l.push(x);}
    void push_back(mint x){r.push(x);}
    void pop_front(){
        assert(k);
        if(l.empty()){
            if(r.size()==1){
                r.pop();
                return;
            }
            rebuild();
        }
        l.pop();
    }
    void pop_back(){
        assert(k);
        if(r.empty()){
            if(l.size()==1){
                l.pop();
                return;
            }
            rebuild();
        }
        r.pop();
    }
    mint get()const{
        return l.get()*r.get()*ifact;
    }
    operator mint()const{return get();}
    void inc_n(){
        if(k){
            pop_front();
            push_back(mint(n+1));
        }
        ++n;
    }
    void dec_n(){
        assert(n>0);
        if(k){
            pop_back();
            push_front(mint(n-k));
        }
        --n;
    }
    void inc_k(){
        push_front(mint(n-k));
        ++k;
        ifact*=binom<mint>::inv(k);
    }
    void dec_k(){
        assert(k>0);
        pop_front();
        ifact*=k;
        --k;
    }
};