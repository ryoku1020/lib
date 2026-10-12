#pragma once
template<class T>
vector<array<T,3>>dyadic(T L,T R){
    T S=1;
    while(S<R)S<<=1;
    vector<array<T,3>>a,b;
    for(T l=L+S,r=R+S,w=1;l<r;l>>=1,r>>=1,w<<=1){
        if(l&1){
            T x=l*w-S;
            a.push_back({x,x+w,l++});
        }
        if(r&1){
            --r;
            T x=r*w-S;
            b.push_back({x,x+w,r});
        }
    }
    reverse(all(b));
    a.insert(a.end(),b.begin(),b.end());
    return a;
}