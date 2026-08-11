#pragma once
template<class mint>
//second[i] が a_{n-i} -> a_n への係数に対応する
pair<int,vc<mint>>BerlekampMassey(vc<mint>S){
    int N=S.size();
    vc<mint>B{1};
    int n0=-1;
    mint b=1;
    int L=0;
    vc<mint>Q{1};
    rep(n,N){
        mint delta=0;
        rep(i,Q.size())delta+=Q[i]*S[n-i];
        if(delta==0)continue;
        int L_new=(2*L<=n?n+1-L:L);
        vc<mint>Q_new=Q;
        Q_new.resize(L_new+1);
        mint c=delta/b;
        rep(i,B.size())Q_new[n-n0+i]-=c*B[i];
        if(2*L<=n){
            swap(B,Q);
            n0=n,b=delta;
        }
        L=L_new;
        Q=Q_new;
    }
    Q*=-1;
    return{L,Q};
}