#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class Line,class T,bool ismin=true>
struct dynamic_li_chao_tree{
    struct Node{
        Line line;
        bool has_line;
        Node*l,*r;
        Node():line(Line::id()),has_line(false),l(nullptr),r(nullptr){}
        ~Node(){
            if(l)delete l;
            if(r)delete r;
        }
    };
    Node*root;
    T n,N;
    dynamic_li_chao_tree(T n_):root(nullptr),n(n_){
        assert(n_>=0);
        N=1;
        while(N<n_)N*=2;
    }
    ~dynamic_li_chao_tree(){if(root)delete root;}
    void add_line_(Line a,Node*&t_ref,T L,T R){
        Node**t=&t_ref;
        while(1){
            if(!(*t))*t=new Node();
            if(!(*t)->has_line){
                (*t)->line=a;
                (*t)->has_line=true;
                return;
            }
            T mid=L+R>>1;
            if(ismin?a.eval(mid)<(*t)->line.eval(mid):a.eval(mid)>(*t)->line.eval(mid))swap((*t)->line,a);
            if(L+1==R)break;
            if(ismin?a.eval(L)<(*t)->line.eval(L):a.eval(L)>(*t)->line.eval(L)){
                t=&((*t)->l);R=mid;
            }else{
                t=&((*t)->r);L=mid;
            }
        }
    }
    void add_line(Line a){add_line_(a,root,0,N);}
    void add_segment_(Line a,Node*&t,T L,T R,T ql,T qr){
        if(qr<=L||R<=ql)return;
        if(ql<=L&&R<=qr){
            add_line_(a,t,L,R);
            return;
        }
        if(!t)t=new Node();
        T mid=L+R>>1;
        add_segment_(a,t->l,L,mid,ql,qr);
        add_segment_(a,t->r,mid,R,ql,qr);
    }
    void add_segment(Line a,T ql,T qr){
        assert(0<=ql&&ql<=qr&&qr<=n);
        add_segment_(a,root,0,N,ql,qr);
    }
    T query(T x){
        assert(0<=x&&x<n);
        Node*t=root;
        T L=0,R=N;
        T res=ismin?inf<T>:-inf<T>;
        while(t){
            if(t->has_line){
                if(ismin)chmin(res,t->line.eval(x));
                else chmax(res,t->line.eval(x));
            }
            T mid=L+R>>1;
            if(x<mid)t=t->l,R=mid;
            else t=t->r,L=mid;
        }
        return res;
    }
};

}
