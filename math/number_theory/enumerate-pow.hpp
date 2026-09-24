#pragma once
template<class mint>
vc<mint>enumerate_pow(int N,ll k){
    vc<mint>f(N+1);
    vc<uint16_t>lp(N+1);
    vc<int>ps;
    if(N>=1)f[1]=1;
    for(int i=2;i<=N;i++){
        if(!lp[i]){
            ps.pb(i);
            f[i]=mint(i).pow(k);
        }
        for(auto p:ps){
            ll x=1LL*i*p;
            if(x>N)break;
            lp[x]=p;
            f[x]=f[i]*f[p];
            if(lp[i]&&p==lp[i])break;
        }
    }
    return f;
}