#pragma once
#include"../../math/modular/dynamic-mod-int.hpp"
template<class Graph>
int chromatic_number(const Graph&g){
    assert(Graph::directed()==false);
    int n=g.size();
    assert(n<32);
    vc<int>adj(n);
    rep(i,n){
        for(auto&e:g[i]){
            if(e.to==i){
                return n+1;
            }
            adj[i]+=1<<e.to;
        }
    }
    vc<int>set_ind(1<<n);set_ind[0]=1;
    REP(i,1,1<<n){
        int add=tbit(i);
        set_ind[i]=set_ind[i^(1<<add)]&((adj[add]&i)==0);
    }
    dbg(set_ind);
    vc<int>set_ind_zeta=set_ind;
    rep(j,n)rep(i,1<<n){
        if(i>>j&1){
            set_ind_zeta[i]+=set_ind_zeta[i^(1<<j)];
        }
    }

    int ans=n;
    using mint=dynamic_modint<20260521>;
    mt19937 mt(random_device{}());
    rep(t,3){
        mint::set_mod((mt()%(int)1e9)+1e7);

        vc<mint>pow_set(1<<n);
        rep(i,1<<n)pow_set[i]=set_ind_zeta[i];
        REP(k,1,n+1){
            mint color=0;
            rep(i,1<<n)
                color+=pow_set[i]*((n-popcount(i))%2?1:-1);

            if(color.val){
                chmin(ans,k);
                break;
            }
            rep(i,1<<n)
                pow_set[i]*=set_ind_zeta[i];
        }
    }   
    return ans;
}
