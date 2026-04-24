#pragma once
#include"../template.hpp"
namespace _G001dENSEARCH{
vc<ull>fib{1,1};
template<class T>
int find_target(T w){
    int ac=fib.size()-2,wa=-1;
    while(ac-wa>1){
        int wj=ac+wa>>1;
        if(fib[wj]>=w)ac=wj;
        else wa=wj;
    }
    return ac;
}
//find-min Comp(a,b) が true で一番強い a を返す tie-break は idx で（小さい方を優先）
template<class T,class G,class F,class Compare=less<G>>
pair<G,T> GoldenSearch(T l,T r,F&get_value,G weakest,Compare Comp=Compare()){
    assert(l<=r);
    if(r-l==0){
        return {get_value(l),l};
    }
    if(r-l==1){
        auto A1=get_value(l);
        auto A2=get_value(l+1);
        if(!Comp(A2,A1))return {A1,l}; 
        return {A2,l+1};
    }
    while(fib.size()<95){
        fib.push_back(fib.back()+fib[fib.size()-2]);
    }
    int fib_idx=find_target(r-l+2);
    T L=l-1,R=L+fib[fib_idx];
    G value_L,value_L1,value_R1,value_R;
    bool done_L1=0,done_R1=0,done_L=0,done_R=0;
    auto Get_value=[&](T a){
        if(a<l||r<a)return weakest;
        return get_value(a);
    };
    while(R-L>2){
        T L1=L+fib[fib_idx-2],R1=L+fib[fib_idx-1];
        if(chmax(done_L1,1))value_L1=Get_value(L1);
        if(chmax(done_R1,1))value_R1=Get_value(R1);
        if(!Comp(value_R1,value_L1)){ 
            R=R1;
            value_R=value_R1;
            value_R1=value_L1;
            done_R1=done_R=1;
            done_L1=0;
        }else{
            L=L1;
            value_L=value_L1;
            value_L1=value_R1;
            done_L1=done_L=1;
            done_R1=0;
        }
        fib_idx--;
    }   
    G Lvalue=done_L?value_L:Get_value(L);
    G L1value=(done_L1?value_L1:done_R1?value_R1:Get_value(L+1));
    G Rvalue=done_R?value_R:Get_value(R);
    T idx=L;
    if(Comp(L1value,Lvalue)){Lvalue=L1value;idx=L+1;}
    if(Comp(Rvalue,Lvalue)){ Lvalue=Rvalue;idx=R;}
    return {Lvalue,idx};
}
}
template<class T,class G,class F,class Compare=less<G>>
auto GoldenSearch(T l,T r,F&get_value,G weakest,Compare Comp=Compare()){
    return _G001dENSEARCH::GoldenSearch<T,G,F,Compare>(l,r,get_value,weakest,Comp);
}