#pragma once
namespace GOLDENSEARCH{
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
pair<G,T> golden_search(T l,T r,F&get_value,G weakest,Compare Comp=Compare()){
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
    G value_l,value_l1,value_r1,value_r;
    bool done_l1=0,done_r1=0,done_l=0,done_r=0;
    auto Get_value=[&](T a){
        if(a<l||r<a)return weakest;
        return get_value(a);
    };
    while(R-L>2){
        T L1=L+fib[fib_idx-2],R1=L+fib[fib_idx-1];
        if(chmax(done_l1,1))value_l1=Get_value(L1);
        if(chmax(done_r1,1))value_r1=Get_value(R1);
        if(!Comp(value_r1,value_l1)){ 
            R=R1;
            value_r=value_r1;
            value_r1=value_l1;
            done_r1=done_r=1;
            done_l1=0;
        }else{
            L=L1;
            value_l=value_l1;
            value_l1=value_r1;
            done_l1=done_l=1;
            done_r1=0;
        }
        fib_idx--;
    }   
    G Lvalue=done_l?value_l:Get_value(L);
    G L1value=(done_l1?value_l1:done_r1?value_r1:Get_value(L+1));
    G Rvalue=done_r?value_r:Get_value(R);
    T idx=L;
    if(Comp(L1value,Lvalue)){Lvalue=L1value;idx=L+1;}
    if(Comp(Rvalue,Lvalue)){ Lvalue=Rvalue;idx=R;}
    return {Lvalue,idx};
}
}
template<class T,class G,class F,class Compare=less<G>>
auto golden_search(T l,T r,F&get_value,G weakest,Compare Comp=Compare()){
    return GOLDENSEARCH::golden_search<T,G,F,Compare>(l,r,get_value,weakest,Comp);
}
