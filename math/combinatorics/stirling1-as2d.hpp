#pragma once
//符号付きでないことに注意すること
template<class mint>
vvc<mint>stirling1_as2d(int n,int m){
    vvc<mint>res(n+1,vc<mint>(m+1));
    res[0][0]=1;
    REP(i,1,n+1){
        REP(j,1,min<int>(i,m)+1){
            res[i][j]=res[i-1][j-1]+res[i-1][j]*(i-1);
        }
    }
    return res;
}