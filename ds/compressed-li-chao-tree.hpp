#pragma once
#include"compresser.hpp"
template<class Info,bool ismin,class T>
struct CompressedLiChaoTree{
    int coef;
    using Line=Info::value_type;
    vc<Line>best_line;
    Compresser<T>cp;
    int n;
    CompressedLiChaoTree(int n=0):cp(n){
        if(ismin)coef=1;
        else coef=-1;
    }
    void add_x(T x){
        assert(!built);
        cp.push(x);
    }
    bool built=0;
    void build(){
        if(!chmax(built,1))return;
        cp.build();
        n=1;while(cp.size()>n)n*=2;
        if(cp.size()==0)cp.push(0);
        while(cp.size()<n)cp.x.push_back(cp.x.back());
        best_line.assign(n*2,Info::e());
    }
private:
    void add_line_(Line a,int now,int L,int R){
        build();
        while(now<n*2){
            int mid=L+R>>1;
            if(Info::eval(a,cp[mid])*coef<Info::eval(best_line[now],cp[mid])*coef)swap(best_line[now],a);
            if(Info::eval(a,cp[L])*coef<Info::eval(best_line[now],cp[L])*coef){
                now=now*2;
                R=mid;
            }else{
                now=now*2+1;
                L=mid;
            }
        }
    }
public:
    void add_line(Line a){
        build();
        add_line_(a,1,0,n);
    }
    void add_segment(Line a,T L,T R){
        assert(L<=R);
        build();
        int l=cp.find_next(L),r=cp.find_next(R);
        assert(l>=0&&l<cp.size()&&cp[l]==L);
        assert(r>=0&&r<cp.size()&&cp[r]==R);
        int sl=l,sr=r;
        int w=1;
        l+=n,r+=n;
        while(l<r){
            if(l&1){add_line_(a,l,sl,sl+w);sl+=w;l++;}
            if(r&1){--r;sr-=w;add_line_(a,r,sr,sr+w);}
            w*=2,l/=2,r/=2;
        }
    }
    T query(T x){
        build();
        int xi=cp.find(x);assert(xi>=0);
        xi+=n;
        T res=inf<T>;
        while(xi){
            chmin(res,Info::eval(best_line[xi],x)*coef);
            xi/=2;
        }
        return res*coef;
    }
};
