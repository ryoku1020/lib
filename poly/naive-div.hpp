#pragma once
#include"base.hpp"
//{F/G,F mod G}
template<class mint>
pair<fps<mint>,fps<mint>>naive_div(fps<mint>F,fps<mint>G){
    while(G.back()==0)G.pop_back();
    assert(G.size());
    while(F.size()&&F.back()==0)F.pop_back();
    mint iG=G.back().inv();
    if(F.size()<G.size()){
        return{{},F};
    }
    fps<mint>res(F.size()-G.size()+1);
    DREP(i,(int)F.size()-1,G.size()-1){
        mint coef=-F[i]*iG;
        REP(j,1,G.size()){
            F[i-j]+=coef*G[G.size()-j-1];
        }
        res[i-(G.size()-1)]=-coef;
    }
    F.resize(G.size()-1);
    return {res,F};
}
template<class mint>
fps<mint>naive_mul(fps<mint>F,fps<mint>G){
    fps<mint>FG(F.size()+G.size()-1);
    rep(i,F.size())rep(j,G.size())FG[i+j]+=F[i]*G[j];
    return FG;
}