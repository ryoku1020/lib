#pragma once
template<class mint>
vc<mint>GcdConvolution(vc<mint>a,vc<mint>b){
    int n=max(a.size(),b.size());
    a.resize(n),b.resize(n);
    vc<mint>c(a.size());
    rep(i,n){
        c[i]+=a[i]*b[0];
        c[i]+=a[0]*b[i];
    }
    c[0]-=a[0]*b[0];
    vc<int>prime(n,1);
    prime[0]=prime[1]=0;
    for(int i=2;i<n;i++){
        if(prime[i])for(int j=i+i;j<n;j+=i){
            prime[j]=0;
        }
    }
    for(int i=2;i<n;i++){
        if(!prime[i])continue;
        for(int j=(n-1)/i;j>=1;j--){
            a[j]+=a[j*i];   
        }
    }
    for(int i=2;i<n;i++){
        if(!prime[i])continue;
        for(int j=(n-1)/i;j>=1;j--){
            b[j]+=b[j*i];   
        }
    }
    rep(i,n)a[i]*=b[i];
    for(int i=2;i<n;i++){
        if(!prime[i])continue;
        for(int j=1;j*i<n;j++){
            a[j]-=a[j*i];   
        }
    }
    rep(i,n)a[i]+=c[i];
    return a;
}