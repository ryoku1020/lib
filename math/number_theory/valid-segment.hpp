#pragma once
//at+b \in [l,r] なる t の閉区間
template<class T>
pair<T,T>validsegment(T a,T b,T l,T r){
    if(a==0){
        if(l<=b&&b<=r)return {-inf<T>,inf<T>};
        return {0,-1};
    }
    if(a>0){
        return {ceil<T>(l-b,a),floor<T>(r-b,a)};
    }else{
        return {ceil<T>(r-b,a),floor<T>(l-b,a)};
    }
}