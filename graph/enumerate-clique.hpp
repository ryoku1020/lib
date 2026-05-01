#pragma once
#include"base.hpp"
template<class G,class F>
void enumerate_clique(const G&g,F f){
    static_assert(G::directed()==false);
    int n=g.size();
    auto adj=g.template adj<int>();
    vc<int>alive(n,1);
    while(sum(alive)){
        pii tar{(int)1e9,(int)1e9};
        rep(i,n)if(alive[i]){
            int cnt=0; 
            rep(j,n)if(alive[j]&&adj[i][j]){
                ++cnt;
            }
            chmin(tar,pii{cnt,(int)i});
        }
        int target=tar.second;
        vc<int>nei;rep(i,n)if(alive[i]&&adj[target][i])nei.pb(i);
        nei.pb(target);
        REP(i,1<<(nei.size()-1),1<<(nei.size())){
            int ng=0;
            rep(j,nei.size())REP(k,j+1,nei.size()){
                if((i>>j&1)&&(i>>k&1)){
                    if(!adj[nei[j]][nei[k]]){
                        ng=1;
                        break;
                    }
                }
            }
            if(!ng){
                vc<int>pt;pt.reserve(popcount(i));
                rep(j,nei.size())if(i>>j&1)pt.pb(nei[j]);
                f(pt);
            }
        }
        alive[target]=0;
    }
}