#pragma once
#include "conv.hpp"
#ifndef FPS_STRUCT
#define FPS_STRUCT
template<class mint>
struct fps:vc<mint>{
    #define BF atcoder::internal::butterfly
    #define IBF atcoder::internal::butterfly_inv
    using vc<mint>::vc;
    using vc<mint>::operator[];
    fps(const vc<mint>&v):vc<mint>(v){}
    fps&operator=(const vc<mint>&v){vc<mint>::operator=(v);return *this;}
    fps&operator+=(const fps&g){
        int n=g.size();
        if(n>(int)this->size())this->resize(n);
        for(int i=0;i<n;i++)(*this)[i]+=g[i];
        return *this;
    }
    fps&operator-=(const fps&g){
        int n=g.size();
        if(n>(int)this->size())this->resize(n);
        for(int i=0;i<n;i++)(*this)[i]-=g[i];
        return *this;
    }
    fps&operator*=(const fps&g){
        if(this->empty()||g.empty()){this->clear();return *this;}
        auto res=atcoder::convolution<mint>(*this,g);
        *this=fps(res.begin(),res.end());
        return *this;
    }
    fps& operator+=(const mint&v){if(this->empty())this->resize(1);(*this)[0]+=v;return *this;}
    fps& operator-=(const mint&v){if(this->empty())this->resize(1);(*this)[0]-=v;return *this;}
    fps& operator*=(const mint&v){for(auto& x:*this)x*=v;return *this;}
    fps& operator/=(const mint&v){mint inv=v.inv();for(auto& x:*this)x*=inv;return *this;}
    fps& operator>>=(const ll&v){*this=fps(this->begin()+min<int>(this->size(),v),this->end());return *this;} 
    fps& operator<<=(const ll&v){fps np(v+this->size());rep(i,this->size())np[i+v]=(*this)[i];*this=np;return *this;}
    fps operator+(const fps&g)const{return fps(*this)+=g;}
    fps operator-(const fps&g)const{return fps(*this)-=g;}
    fps operator*(const fps&g)const{return fps(*this)*=g;}
    fps operator+(const mint&v)const{return fps(*this)+=v;}
    friend fps operator+(const mint&v,const fps&g){return fps(g)+=v;}
    fps operator-(const mint&v)const{return fps(*this)-=v;}
    friend fps operator-(const mint&v,const fps&g){return -g+=v;}
    fps operator*(const mint&v)const{return fps(*this)*=v;}
    friend fps operator*(const mint&v,const fps&g){return fps(g)*=v;}
    fps operator/(const mint&v)const{return fps(*this)/=v;}
    friend fps operator/(const mint&v,const fps&g){return fps(g)/=v;}
    fps operator>>(const ll&v)const{return fps(*this)>>=v;}
    fps operator<<(const ll&v)const{return fps(*this)<<=v;}
    fps operator-()const{
        fps res=*this;
        for(auto&x:res)x=-x;
        return res;
    }
    fps pre(int sz)const{
        return fps(this->begin(),this->begin()+min((int)this->size(),sz));
    }
    //[0,n)
    fps inv(int deg=-1)const{
        assert((*this).size()&&(*this)[0].val!=0);
        if(deg==-1)deg=this->size();
        fps res{(*this)[0].inv()};
        for(int len=1;len<deg;len*=2){
            int nxt=len*2;
            auto F=(*this).pre(len*2);
            auto res2=res;
            F.resize(nxt);
            res2.resize(nxt);
            BF(F);
            BF(res2);
            rep(i,res2.size())F[i]*=res2[i];
            IBF(F);
            mint inv=1/mint(nxt);F*=inv;
            rep(i,len)F[i]=0;REP(i,len,len*2)F[i]=-F[i];
            BF(F);
            rep(i,res2.size())F[i]*=res2[i];
            IBF(F);
            F*=inv;
            res.resize(len*2);
            REP(i,len,len*2)res[i]=F[i];
        }
        res.resize(deg);
        return res;
    }
    fps diff()const{
        auto res=*this;
        rep(i,res.size())res[i]*=i;
        if(res.size())res.erase(res.begin());
        return res;
    }
    fps integral()const{
        fps res(this->size()+1);
        rep(i,this->size())res[i+1]=(*this)[i]*Binom<mint>::inv(i+1);
        return res;
    }
    fps log(int deg=-1)const{
        if(deg==-1)deg=this->size();
        assert(this->size()&&(*this)[0]==1);
        return (this->diff().pre(deg)*this->inv(deg)).integral().pre(deg);
    }
    fps exp(int deg=-1)const{
        assert((*this).size()&&(*this)[0]==0); 
        if(deg==-1)deg=this->size();
        fps res{1},h{1};
        for(int len=1;len<deg;len*=2){
            int nxt=len*2;
            mint inv=1/mint(nxt);
            fps G=res;G.resize(nxt);BF(G);
            fps H=h;H.resize(nxt);BF(H);
            fps V=G;
            rep(i,nxt)V[i]*=H[i];
            IBF(V);rep(i,nxt)V[i]*=inv;
            rep(i,len)V[i]=0;REP(i,len,nxt)V[i]=-V[i];
            BF(V);
            fps g_prime(nxt);
            rep(i,len-1)g_prime[i]=res[i+1]*(i+1);
            BF(g_prime);
            fps f_prime(nxt);
            rep(i,len)if(i+1<(int)this->size())f_prime[i]=(*this)[i+1]*(i+1);
            BF(f_prime);
            fps w_prime(nxt);
            rep(i,nxt)w_prime[i]=g_prime[i]*H[i]+f_prime[i]*V[i];
            IBF(w_prime);w_prime*=inv;
            DREP(i,nxt-1,len){
                mint fi=(i<(int)this->size())?(*this)[i]:0;
                w_prime[i]=fi-w_prime[i-1]*Binom<mint>::inv(i);
            }
            rep(i,len)w_prime[i]=0;
            BF(w_prime);
            rep(i,nxt)G[i]*=w_prime[i];
            IBF(G);G*=inv;
            res.resize(nxt);
            REP(i,len,nxt)res[i]=G[i];
            if(nxt<deg){
                rep(i,nxt)H[i]*=(V[i]-w_prime[i]);
                IBF(H);rep(i,nxt)H[i]*=inv;
                h.resize(nxt);
                REP(i,len,nxt)h[i]=H[i];
            }
        }
        res.resize(deg);
        return res;
    }
    fps pow(ll m,int deg=-1)const{
        if(deg==-1)deg=this->size();
        if(m==0){fps res(deg);res[0]=1;return res;}
        rep(i,this->size()){
            if(m*i>=deg)return fps(deg);
            if((*this)[i].val){
                auto target=(*this)>>i;
                mint coef=mint((*this)[i]);
                mint inv=1/coef;
                target*=inv; 
                return ((m*target.log(deg-i*m)).exp(deg-i*m)*mint(coef).pow(m))<<(i*m);
            }
        }
        return fps(deg);
    }
    void extend(int n){
        if(this->size()<n)this->resize(n);
    }
    fps shrink(){
        auto res=(*this);
        while(res.size()&&res.back()==0)res.pop_back();
        return res;
    }
    pair<fps,fps>div(fps f)const{
        if(this->size()<f.size()){ 
            return {{},(*this)}; 
        }
        int qsize=this->size()-f.size()+1;
        auto rthis=*this;reverse(all(rthis));
        auto rf=f;reverse(all(rf));
        auto rq=(rthis.pre(qsize)*rf.inv(qsize)).pre(qsize);
        reverse(all(rq));
        return {rq,(*this-rq*f).shrink()};
    }
    fps div_only(fps f)const{
        if(this->size()<f.size()){ 
            return {{}}; 
        }
        int qsize=this->size()-f.size()+1;
        auto rthis=*this;reverse(all(rthis));
        auto rf=f;reverse(all(rf));
        auto rq=(rthis.pre(qsize)*rf.inv(qsize)).pre(qsize);
        reverse(all(rq));
        return rq;
    }
    
    optional<fps> sqrt(int deg=-1)const{
        if(deg==-1)deg=this->size();
        if((this)->size()==0)return fps(deg);
        if((*this)[0]==0){
            REP(i,1,this->size()){
                if((*this)[i].val){
                    if(i%2)return nullopt; 
                    if(deg-i/2<=0)break;
                    auto res=((*this)>>i).sqrt(deg-i/2);
                    if(!res.has_value())return nullopt;
                    auto ret=res.value();
                    ret<<=(i/2);
                    ret.resize(deg);
                    return ret;
                }
            }
            return fps(deg);
        }
        ll s=ModSqrt((*this)[0].val,mint::get_mod());
        if(s==-1)return nullopt;
        fps res{s};
        mint inv=1/mint(2);
        for(int i=1;i<deg;i*=2){
            res=(res+(*this).pre(i<<1)*res.inv(i<<1))*inv;
        }
        return res.pre(deg);
    }
    //f(x) -> f(vx)
    fps substitute(mint v){
        mint coef=1;
        fps nxt(*this);rep(i,nxt.size()){
            nxt[i]*=coef;
            coef*=v;
        }
        return nxt;
    }
};
#endif
