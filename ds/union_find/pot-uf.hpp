#pragma once

template<class X>
struct potentialized_union_find{
    using value_type=X::value_type;
    vc<int>par;
    //val[par[x]]=val[x]*w[x]
    vc<value_type>w;
    potentialized_union_find(int n){
        assert(n>=0);
        par.assign(n,-1);
        w.assign(n,X::e());
    }
    int root(int x){
        assert(0<=x&&x<par.size());
        if(par[x]<0)return x;
        else{
            auto res=root(par[x]);
            w[x]=X::op(w[x],w[par[x]]);
            return par[x]=res;
        }
    }
    int same(int x,int y){
        assert(0<=x&&x<par.size()&&0<=y&&y<par.size());
        return root(x)==root(y);
    }
    //assume that same(x,y)=1
    //val[x]^{-1}*val[y] 
    value_type diff(int x,int y){
        assert(0<=x&&x<par.size()&&0<=y&&y<par.size());
        assert(same(x,y));
        return X::op(w[x],X::inv(w[y]));
    }
    //val[x]=val[y]*W 
    int merge(int x,int y,value_type W){
        assert(0<=x&&x<par.size()&&0<=y&&y<par.size());
        if(same(y,x)){
            if(diff(y,x)!=W)return -1;
            return 0;
        }
        W=X::op(X::op(X::inv(w[y]),W),w[x]);
        x=root(x),y=root(y);
        par[x]+=par[y];
        par[y]=x;
        w[y]=W;
        return 1;
    }
};
