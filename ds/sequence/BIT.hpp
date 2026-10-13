#pragma once
#include"../../template.hpp"
namespace ryoku{
template<class T=long long>
struct binary_indexed_tree{
    int n;
    std::vector<T>data;
    binary_indexed_tree():n(0),data(0){}
    binary_indexed_tree(int N):n(N){
        assert(N>=0);
        data.assign(N,0);
    }
    binary_indexed_tree(const std::vector<T>& a):n(a.size()),data(a){
        for(int i=1;i<=n;i++){
            int j=i+(i&-i);
            if(j<=n)data[j-1]+=data[i-1];
        }
    }
    void add(int i,T x){
        assert(i>=0&&i<n);
        for(i++;i<=n;i+=(i&-i))data[i-1]+=x;
    }
    //[l,r) 
    void range_add(int l,int r,T x){
        add(l,x);
        add(r,-x);
    }
    T get(int r){
        return internal_sum(r+1);
    }
    T internal_sum(int r)const{
        assert(0<=r&&r<=n);
        T ret=0;
        for(;r>0;r-=(r&-r))ret+=data[r-1];
        return ret;
    }
    T sum(int l,int r)const{
        assert(0<=l&&l<=r&&r<=n);
        return internal_sum(r)-internal_sum(l);
    }
    int lower_bound(T w)const{
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
template<class T=long long>
using bit=binary_indexed_tree<T>;

}

#ifdef LOCAL
#include"../../debug/formatters/ds--sequence--BIT.hpp"
#endif
