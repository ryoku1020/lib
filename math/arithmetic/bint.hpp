#pragma once
#include"../convolution/conv.hpp"
struct bint{
    using u32=uint32_t;
    using u64=uint64_t;
    static const u32 w=30;
    static const u32 MAX=1u<<w;
    static const u32 MASK=MAX-1;
    vc<u32>digit;
    int sign=0;
    bint(){}
    bint(ll x){
        if(x==0)return;
        if(x>0)sign=1;
        else if(x<0)sign=-1;
        digit.pb(x&MASK);
        if(x>>w)digit.pb(x>>w);
    }
    void normalize(){
        while(digit.size()&&digit.back()==0){
            digit.pop_back();
        }
        if(digit.size()==0){
            sign=0;
        }
    }
    int size()const{
        return digit.size();
    }
    static bint naivemul(const bint&lhs,const bint&rhs){
        if(lhs.sign==0||rhs.sign==0)return {};
        vc<u32>ans(rhs.digit.size()+lhs.digit.size());
        rep(i,lhs.size()){
            u64 carry=0;
            rep(j,rhs.size()){
                u64 cur=(u64)lhs.digit[i]*rhs.digit[j]+ans[i+j]+carry;
                ans[i+j]=cur&MASK;
                carry=cur>>w;
            }
            ans[i+rhs.size()]+=carry;
        }
        bint lrhs;
        lrhs.sign=lhs.sign*rhs.sign;
        lrhs.digit=move(ans);
        lrhs.normalize();
        return lrhs;
    }
    //|lhs|<|rhs| -1
    //|lhs|>|rhs| 1
    //|lhs|=|rhs| 0
    static int cmpabs(const bint&lhs,const bint&rhs){
        if(lhs.size()!=rhs.size())return lhs.size()<rhs.size()?-1:1;
        drep(i,lhs.size()){
            if(lhs.digit[i]!=rhs.digit[i]){
                return lhs.digit[i]<rhs.digit[i]?-1:1;
            }
        }
        return 0;
    }
    static void addabs(bint&lhs,const bint&rhs){
        if(lhs.size()<rhs.size()){
            lhs.digit.resize(rhs.size());
        }
        u32 carry=0;
        rep(i,rhs.size()){
            lhs.digit[i]+=rhs.digit[i]+carry;
            carry=lhs.digit[i]>>w;
            lhs.digit[i]&=MASK;
        }
        int idx=rhs.size();
        while(carry){
            if(idx==lhs.size()){
                lhs.digit.pb(carry);
                break;
            }
            lhs.digit[idx]+=carry;
            carry=lhs.digit[idx]>>w;
            lhs.digit[idx++]&=MASK;
        }
        lhs.normalize();
    }
    static void subabs(bint&lhs,const bint&rhs){
        u32 borrow=0;
        rep(i,rhs.size()){
            u32 sub=rhs.digit[i]+borrow;

            if(lhs.digit[i]<sub){
                lhs.digit[i]=lhs.digit[i]+MAX-sub;
                borrow=1;
            }else{
                lhs.digit[i]-=sub;
                borrow=0;
            }
        }
        int idx=rhs.size();
        while(borrow){
            if(lhs.digit[idx]==0){
                lhs.digit[idx]=MASK;
                ++idx;
            }else{
                --lhs.digit[idx];
                borrow=0;
            }
        }
        lhs.normalize();
    }
    
    bint&operator+=(bint rhs){
        auto&lhs=*this;
        if(lhs.sign==rhs.sign){
            addabs(lhs,rhs);
        }else{
            if(cmpabs(lhs,rhs)<0){
                swap(lhs,rhs);
            }
            subabs(lhs,rhs);
        }
        return lhs;
    }
    bint operator-() const{
        auto res=*this;res.sign*=-1;
        return res;
    }
    bint&operator-=(bint rhs){
        rhs.sign*=-1;
        return (*this)+=move(rhs);
    }
    static bint convmul(const bint& lhs,const bint& rhs){
        if(lhs.sign==0||rhs.sign==0)return {};
        const u32 W2=w/2;
        const u32 MASK2=(1u<<W2)-1;
        vc<ll> a(lhs.size()*2),b(rhs.size()*2);
        rep(i,lhs.size()){
            a[2*i]=lhs.digit[i]&MASK2;
            a[2*i+1]=lhs.digit[i]>>W2;
        }
        rep(i,rhs.size()){
            b[2*i]=rhs.digit[i]&MASK2;
            b[2*i+1]=rhs.digit[i]>>W2;
        }
        auto c=atcoder::convolution_ll(a,b);
        ll carry=0;
        rep(i,c.size()){
            c[i]+=carry;
            carry=c[i]>>W2;
            c[i]&=MASK2;
        }
        while(carry){
            c.pb(carry&MASK2);
            carry>>=W2;
        }
        bint res;
        res.sign=lhs.sign*rhs.sign;
        res.digit.resize((c.size()+1)/2);
        rep(i,res.digit.size()){
            u32 low=c[2*i];
            u32 high=(2*i+1<(int)c.size()?c[2*i+1]:0);
            res.digit[i]=low|(high<<W2);
        }
        res.normalize();
        return res;
    }
    static const int THRESHOLD=50;
    bint&operator*=(const bint& rhs){
        if(sign==0||rhs.sign==0){
            *this=bint{};
            return *this;
        }   

        if(min(size(),rhs.size())<=THRESHOLD){
            *this=naivemul(*this,rhs);
        }else{
            *this=convmul(*this,rhs);
        }
        return *this;
    }
};
