#pragma once
//max で eval されるので注意
template<class Info,bool ismin,class T>
struct DynamicLiChaoTree{
    using Line=typename Info::value_type;
    struct Node{
        Line line;
        Node*l,*r;
        Node():line(Info::e()),l(nullptr),r(nullptr){}
        ~Node(){
            if(l)delete l;
            if(r)delete r;
        }
    };
    Node*root;
    T n,N;
    int coef;
    DynamicLiChaoTree(T n_):root(nullptr),n(n_){
        N=1;
        while(N<n_)N*=2;
        if(ismin)coef=1;
        else coef=-1;
    }
    ~DynamicLiChaoTree(){if(root)delete root;}
    void add_line_(Line a,Node*&t_ref,T L,T R){
        Node**t=&t_ref;
        while(1){
            if(!(*t))*t=new Node();
            T mid=L+R>>1;
            if(Info::eval(a,mid)*coef<Info::eval((*t)->line,mid)*coef)swap((*t)->line,a);
            if(L+1==R)break;
            if(Info::eval(a,L)*coef<Info::eval((*t)->line,L)*coef){
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
    void add_segment(Line a,T ql,T qr){add_segment_(a,root,0,N,ql,qr);}
    auto query(T x){
        assert(0<=x&&x<n);
        Node*t=root;
        T L=0,R=N;
        using R_t=decltype(Info::eval(Info::e(),x));
        R_t res=inf<R_t>;
        while(t){
            chmin(res,Info::eval(t->line,x));
            T mid=L+R>>1;
            if(x<mid)t=t->l,R=mid;
            else t=t->r,L=mid;
        }
        return ismin?res:-res;
    }
};