#pragma once
template<class T>
vc<int>argument_rank(const vc<pair<T,T>>&a){
    int n=a.size();
    vc<int>p,res(n,-1);
    rep(i,n)if(a[i].first!=0||a[i].second!=0)p.pb(i);
    auto half=[&](int i){
        auto[x,y]=a[i];
        return y<0||(y==0&&x<0);
    };
    auto cross=[&](int i,int j){
        auto[x1,y1]=a[i];
        auto[x2,y2]=a[j];
        if constexpr(is_integral_v<T>){
            __int128 z=(__int128)x1*y2-(__int128)y1*x2;
            return (z>0)-(z<0);
        }else{
            auto z=x1*y2-y1*x2;
            return (z>0)-(z<0);
        }
    };
    sort(all(p),[&](int i,int j){
        if(half(i)!=half(j))return half(i)<half(j);
        return cross(i,j)>0;
    });
    int m=p.size();
    for(int l=0;l<m;){
        int r=l+1;
        while(r<m&&half(p[l])==half(p[r])&&cross(p[l],p[r])==0)++r;
        REP(i,l,r)res[p[i]]=l;
        l=r;
    }
    return res;
}