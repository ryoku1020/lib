#pragma once
#include"../../template.hpp"
#include"../compress.hpp"
namespace ryoku{
template<class Line,class T,bool ismin=true>
struct compressed_li_chao_tree{
    vc<Line>best_line;
    vc<bool>has_line;
    compresser<T>cp;
    int n;
    compressed_li_chao_tree(int n=0):cp(n){}
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
        best_line.assign(n*2,Line::id());
        has_line.assign(n*2,false);
    }
private:
    void add_line_(Line a,int now,int L,int R){
        build();
        while(now<n*2){
            if(!has_line[now]){
                best_line[now]=a;
                has_line[now]=true;
                return;
            }
            int mid=L+R>>1;
            if(ismin?a.eval(cp[mid])<best_line[now].eval(cp[mid]):a.eval(cp[mid])>best_line[now].eval(cp[mid]))swap(best_line[now],a);
            if(ismin?a.eval(cp[L])<best_line[now].eval(cp[L]):a.eval(cp[L])>best_line[now].eval(cp[L])){
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
