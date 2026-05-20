#pragma once
template<class T,T MAXVALUE=numeric_limits<T>::max()/2>
struct SlopeTrick{
    T min_value=0;
    bipq<T>L;
    smpq<T>R;
    T Loffset=0;
    T Roffset=0;
    SlopeTrick(){}
    //offset 適当なので注意
    T get_ltop(){
        return L.empty()?-MAXVALUE:L.top();
    }

    T get_rtop(){
        return R.empty()?MAXVALUE:R.top();
    }
    //f(x) <- f(x)+max(x-a,0)
    void add_R(T a){
        dbg("R",a);
        a-=Loffset;
        L.push(a);
        R.push(L.top()+Loffset-Roffset);
        min_value+=max<T>(get_ltop()-a,0);L.pop();
    }
    //f(x) <- f(x)+max(a-x,0)
    void add_L(T a){
        dbg("L",a);
        a-=Roffset;
        R.push(a);
        L.push(R.top()+Roffset-Loffset);
        min_value+=max<T>(a-get_rtop(),0);R.pop();
    }
    //f(x) <- f(x)+max(a-x,x-a)
    void add_both(T a){
        add_L(a),add_R(a);
    }
    //f(x) <- min {x-L<=a<=x-R} f(a)
    void slide_min(T L,T R){
        assert(L<=R);
        Loffset+=L;
        Roffset+=R;
    }
};
