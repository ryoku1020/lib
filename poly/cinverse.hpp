#include"base.hpp"
template<class mint>
vc<fps<mint>>twodmul(vc<fps<mint>>f,vc<fps<mint>>g){
    int N=1;for(auto&x:f)chmax(N,x.size());for(auto&x:g)chmax(N,x.size());
    int M=max(f.size(),g.size());
    f.resize(M),g.resize(M);
    for(auto&x:f)x.resize(N);
    for(auto&x:g)x.resize(N);
    int padding=N*2;
    fps<mint>F(padding*(M-1)+N),G(F.size());
    rep(i,M)rep(j,N){
        F[i*padding+j]+=f[i][j];
        G[i*padding+j]+=g[i][j];
    }
    F*=G;
    vc<fps<mint>>res(M*2-1,fps<mint>(N*2-1));
    rep(i,M*2-1)rep(j,N*2-1){
        if(i*padding+j<F.size()){
            res[i][j]+=F[i*padding+j];
        }
    }
    return res;
}
template<class mint>
//i=0,1,\dots,m-1 [x^{n-1}] f(x)^i g(x)
fps<mint>power_projection(fps<mint>f,fps<mint>g,ll n,ll m){
    ll N=1;while(N<n)N*=2;
    f.resize(N);

    fps<mint>ng(N);
    rep(i,min<ll>(g.size(),n)){
        ng[i+N-n]=g[i];
    }
    g=ng;
    vc<fps<mint>>px={g};
    vc<fps<mint>>qx={{1},{-f}};
    auto odd=[&](const fps<mint>&f){
        fps<mint>res(f.size()/2);
        rep(i,f.size())if(i%2)res[i/2]=f[i];
        return res;
    };
    auto even=[&](const fps<mint>&f){
        fps<mint>res((f.size()+1)/2);
        rep(i,f.size())if(i%2==0)res[i/2]=f[i];
        return res;
    };
    while(N>1){
        vc<fps<mint>>qxm=qx;
        for(auto&x:qxm)x=x.substitute(-1);
        px=twodmul(px,qxm);
        qx=twodmul(qx,qxm);
        N/=2;
        for(auto&x:px)x=odd(x),x.resize(N);
        for(auto&x:qx)x=even(x),x.resize(N);
        if(px.size()>m)px.resize(m);
        if(qx.size()>m)qx.resize(m);
    }
    fps<mint>rpx(px.size()),rqx(qx.size());
    rep(i,px.size())rpx[i]=px[i][0];
    rep(i,qx.size())rqx[i]=qx[i][0];
    rpx*=rqx.inv(m);
    rpx.resize(m);
    return rpx;
}
template<class mint>
fps<mint>cinverse(fps<mint>f){
    if(f.size()==0)return{};
    if(f.size()==1)return{1};
    mint c=1/f[1];
    f*=c;
    int fd=f.size()-1;
    fps<mint>cfs=power_projection(f,{1},fd+1,fd+1);
    cfs*=mint(fd);
    fps<mint>gfs(fd+1);
    REP(i,1,fd+1){
        gfs[fd-i]=cfs[i]/i;
    }
    gfs=gfs.log();
    gfs/=-(fd);
    gfs=gfs.exp();
    gfs.insert(gfs.begin(),0);
    gfs.resize(f.size());
    gfs=gfs.substitute(c);
    return gfs;
}