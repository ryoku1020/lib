#pragma once
#include "../../template.hpp"
namespace ryoku{
struct undoable_union_find{
    vc<int>par;
    vc<array<int,3>>history;
    int cnt,t=0;
    undoable_union_find(int n):par(n,-1),cnt(n){}
    int root(int x)const{
        assert(0<=x&&x<(int)par.size());
        while(par[x]>=0)x=par[x];
        return x;
    }
    bool same(int x,int y)const{
        return root(x)==root(y);
    }
    int size(int x)const{
        return -par[root(x)];
    }
    bool merge(int x,int y){
        t++;
        x=root(x),y=root(y);
        if(x==y)return false;
        if(par[x]>par[y])swap(x,y);
        history.pb({t,y,par[y]});
        par[x]+=par[y];
        par[y]=x;
        cnt--;
        return true;
    }
    void undo(){
        assert(t>0);
        if(!history.empty()&&history.back()[0]==t){
            auto [tt,y,py]=history.back();
            history.pop_back();
            int x=par[y];
            par[x]-=py;
            par[y]=py;
            cnt++;
        }
        t--;
    }
    void rollback(int k){
        assert(0<=k&&k<=t);
        while(k--)undo();
    }
    void rollback(){
        rollback(t);
    }
    void save(){
        history.clear();
        t=0;
    }
    int count()const{
        return cnt;
    }
};
}
#ifdef LOCAL
#include "../../debug/formatters/ds--union_find--undo-uf.hpp"
#endif