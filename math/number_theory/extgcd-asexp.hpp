#pragma once
//ax+by=c
//res.fi.fi*t+res.fi.se, res.se.fi*t+res.se.se という解集合
template<class T>
pair<pair<T,T>,pair<T,T>>extgcdasexp(T a,T b,T c){
    T g=gcd(a,b);
    assert(a||b);
    if(c%g)return {{-inf<T>,-inf<T>},{-inf<T>,-inf<T>}};
    c/=g,a/=g,b/=g;
    T x,y;
    extgcd(a,b,x,y);
    x*=c,y*=c;
    return {{-b,x},{a,y}};
}