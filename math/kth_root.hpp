#pragma once
#include"../template.hpp"
//floor(a^{1/b})
ull kth_root(ull a,ull b){
    if(a==0)return 0;
    if(b==1)return a;
    if(b>=64)return 1;
    auto my_pow=[&](ull A,ull B)->ull{
        ull res=1;
        while(B){
            if(B%2){
                if(i128(res)*A>a)return 0;
                res*=A;
            }
            B/=2;
            if(B){
                if(i128(A)*A>a)return 0;
                A*=A;
            }
        }
        return res;
    };
    ull ac=1,wa=(ull(1)<<(64/b+1))+1;
    while(wa-ac>1){
        ull wj=ac+wa>>1;
        auto res=my_pow(wj,b);
        if(res&&res<=a){
            ac=wj;
        }else wa=wj;
    }
    return ac;
}