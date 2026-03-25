#pragma once
#include"../template.cpp"
template<class T=long long>
struct BIT{
    int n;
    std::vector<T>data;
    BIT():n(0),data(0){}
    BIT(int N):n(N),data(N,0){}
    BIT(const std::vector<T>& a):n(a.size()),data(a){
        for(int i=1;i<=n;i++){
            int j=i+(i&-i);
            if(j<=n)data[j-1]+=data[i-1];
        }
    }
    void add(int i,T x){
        assert(i>=0&&i<n);
        for(i++;i<=n;i+=(i&-i))data[i-1]+=x;
    }
    T internal_sum(int r){
        T ret=0;
        for(;r>0;r-=(r&-r))ret+=data[r-1];
        return ret;
    }
    T sum(int l,int r){
        assert(0<=l&&l<=r&&r<=n);
        return internal_sum(r)-internal_sum(l);
    }
    int lower_bound(T w){
        if(w<=0)return 0;
        int x=0,r=1;
        while(r<n)r<<=1;
        for(int len=r;len>0;len>>=1){
            if(x+len<=n&&data[x+len-1]<w){
                w-=data[x+len-1];
                x+=len;
            }
        }
        return x;
    }
};