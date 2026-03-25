#pragma once
#include"../template.hpp"
template<class T,auto op,int extra>
struct base_dsu{
        vector<int>par;
        vector<T>data;
        base_dsu(int n):par(n,-1){
            static_assert(!extra,"e is needed");
        }
        base_dsu(int n,T e):par(n,-1),data(n,e){}
        T& operator[](int i){
            static_assert(extra,"No data");
            return data[leader(i)];
        }
        int root(int x){
            if(par[x]<0)return x;
            else return par[x]=root(par[x]);
        }
        bool same(int x,int y){
            return root(x)==root(y);
        }
        bool merge(int x,int y){
            x=root(x);
            y=root(y);
            if(x==y)return false;
            if(par[x]>par[y])swap(x,y);
            par[x]+=par[y];
            par[y]=x;
            if constexpr(extra){
                data[x]=op(data[y],data[x]);
            }
            return true;
        }
        int size(int x){
            return -par[root(x)];
        }
        int leader(int x){
            return root(x);
        }
};
int tf323(int a,int b){return a;}
using DisjointSetUnion =base_dsu<int,tf323,0>;
template<class T,auto op>
using extra_dsu=base_dsu<T,op,1>;