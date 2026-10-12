#pragma once
namespace ryoku{
template<class T>
struct Clamp{
    struct S{
        T a,b,c;
        // min(c,max(b,x+a))
        T eval(T x)const{
            return min(c,max(b,x+a));
        }

    };
    using value_type=S;
    static S op(S x,S y){
        return{x.a+y.a,y.eval(x.b),y.eval(x.c)};
    }
    static S id(){
        return{0,-inf<T>,inf<T>};
    }
};
}