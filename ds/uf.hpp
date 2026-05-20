#pragma once
template<class T,auto op,int extra>
struct BaseDisjointSetUnion{
        vector<int>par;
        vector<T>data;
        BaseDisjointSetUnion(int n):par(n,-1){
            static_assert(!extra,"e is needed");
        }
        BaseDisjointSetUnion(int n,T e):par(n,-1),data(n,e){}
        T& operator[](int i){
            static_assert(extra,"No data");
            return data[leader(i)];
        }
        int root(int x){
            assert(0<=x&&x<par.size());
            if(par[x]<0)return x;
            else return par[x]=root(par[x]);
        }
        bool same(int x,int y){
            assert(0<=x&&x<par.size()&&0<=y&&y<par.size());
            return root(x)==root(y);
        }
        bool merge(int x,int y){
            assert(0<=x&&x<par.size()&&0<=y&&y<par.size());
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
            assert(0<=x&&x<par.size());
            return -par[root(x)];
        }
        int leader(int x){
            assert(0<=x&&x<par.size());
            return root(x);
        }

};
int tf323(int a,int b){return a;}
using DisjointSetUnion=BaseDisjointSetUnion<int,tf323,0>;
template<class T,auto op>
using ExtraDisjointSetUnion=BaseDisjointSetUnion<T,op,1>;