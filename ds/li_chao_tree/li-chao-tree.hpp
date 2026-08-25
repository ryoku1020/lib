#pragma once
template<class info,bool ismin>
struct li_chao_tree{
    int coef;
    using Line=info::value_type;
    vc<Line>best_line;
    int n;
    int in;
    li_chao_tree(int n_):in(n_){
        assert(n_>=0);
        int N=1;
        while(N<n_)N*=2;
        n=N;
        best_line=vc<Line>(N*2,info::e());
        if(ismin)coef=1;
        else coef=-1;
    }
    void add_line_(Line a,int now,int L,int R){
        while(now<n*2){
            int mid=L+R>>1;
            if(info::eval(a,mid)*coef<info::eval(best_line[now],mid)*coef)swap(best_line[now],a);
            if(info::eval(a,L)*coef<info::eval(best_line[now],L)*coef){
                now=now*2;
                R=mid;
            }else{
                now=now*2+1;
                L=mid;
            }
        }
    }
    void add_line(Line a){
        add_line_(a,1,0,n);
    }
    void add_segment(Line a,int l,int r){
        assert(0<=l&&l<=r&&r<=in);
        int sl=l,sr=r;
        int w=1;
        l+=n,r+=n;
        while(l<r){
            if(l&1)add_line_(a,l++,sl,sl+=w);
            if(r&1)add_line_(a,--r,sr-w,sr),sr-=w;
            w*=2,l/=2,r/=2;
        }
    }
    template<class T>
    T query(T x){
        assert(0<=x&&x<in);
        T X=x;
        x+=n;
        T res=inf<T>*coef;
        while(x){
            chmin(res,info::eval(best_line[x],X)*coef);
            x/=2;
        }
        return res*coef;
    }
};
