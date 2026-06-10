#pragma once
//0,1,..,M-1
template<class mint>
vc<mint>LcmConvolution(vc<mint>a,vc<mint>b,int M){
    a.resize(M),b.resize(M);
    vc<mint>c(M);
    rep(i,M){
        c[0]+=a[i]*b[0];
        c[0]+=a[0]*b[i];
    }
    c[0]-=a[0]*b[0];
    vc<int>prime(M,1);
    prime[0]=prime[1]=0;
    for(int i=2;i<M;i++){
        if(prime[i])for(int j=i+i;j<M;j+=i){
            prime[j]=0;
        }
    }
    for(int i=2;i<M;i++){
        if(!prime[i])continue;
        for(int j=1;j*i<M;j++){
            a[j*i]+=a[j];   
        }
    }
    for(int i=2;i<M;i++){
        if(!prime[i])continue;
        for(int j=1;j*i<M;j++){
            b[j*i]+=b[j];   
        }
    }
    rep(i,M)a[i]*=b[i];
    for(int i=2;i<M;i++){
        if(!prime[i])continue;
        for(int j=(M-1)/i;j>=1;j--){
            a[j*i]-=a[j];  
        }
    }
    rep(i,M)a[i]+=c[i];
    return a;
}