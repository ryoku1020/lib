#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class Line,class T,bool ismin=true>
struct li_chao_tree{
    vc<Line>best_line;
    vc<bool>has_line;
    int n;
    int in;
    li_chao_tree(int n_):in(n_){
        assert(n_>=0);
        int N=1;
        while(N<n_)N*=2;
        n=N;
        best_line=vc<Line>(N*2,Line::id());
        has_line=vc<bool>(N*2,false);
    }
    void add_line_(Line a,int now,int L,int R){
        while(now<n*2){
            if(!has_line[now]){
                best_line[now]=a;
                has_line[now]=true;
                return;
            }
            int mid=L+R>>1;
            if(ismin?a.eval(mid)<best_line[now].eval(mid):a.eval(mid)>best_line[now].eval(mid))swap(best_line[now],a);
            if(ismin?a.eval(L)<best_line[now].eval(L):a.eval(L)>best_line[now].eval(L)){
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
            if(l&1){add_line_(a,l,sl,sl+w);sl+=w;l++;}
            if(r&1)add_line_(a,--r,sr-w,sr),sr-=w;
            w*=2,l/=2,r/=2;
        }
    }
    T query(T x){
        assert(0<=x&&x<in);
        int xi=x;
        xi+=n;
        T res=ismin?inf<T>:-inf<T>;
        while(xi){
            if(has_line[xi]){
                if(ismin)chmin(res,best_line[xi].eval(x));
                else chmax(res,best_line[xi].eval(x));
            }
            xi/=2;
        }
        return res;
    }
};

}
