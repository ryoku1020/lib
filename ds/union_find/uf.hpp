#pragma once
template<class T,auto op,int extra>
struct base_disjoint_set_union{
        vector<int>par;
        vector<T>data;
        base_disjoint_set_union(int n){
            static_assert(!extra,"e is needed");
            assert(n>=0);
            par.assign(n,-1);
        }
        base_disjoint_set_union(int n,T e){
            assert(n>=0);
            par.assign(n,-1);
            data.assign(n,e);
        }
        T& operator[](int i){
            static_assert(extra,"no data");
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
using disjoint_set_union=base_disjoint_set_union<int,tf323,0>;
template<class T,auto op>
using extra_disjoint_set_union=base_disjoint_set_union<T,op,1>;
