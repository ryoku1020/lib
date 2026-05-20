#pragma once
template<class T,class F>
vector<T>monotone_minima(F&a,int h,int w,int ismax=0){//関数Fに対してminを求める

    vector<T>res(h);
    auto solve=[&](auto&solve,int l,int r,int x,int y)->void{//[x,y) [l,r)について解く
        if(x>=y)return;
        int mid=(x+y)/2;
        pair<T,int>ans=pair<T,int>({(ll)4e18/2+1,4e18},l);
        for(int i=l;i<r;i++){
            ans=min(ans,make_pair(a(mid,i),i));
        }
        solve(solve,l,ans.second+1,x,mid);
        solve(solve,ans.second,r,mid+1,y);
        res[mid]=ans.first;
    };solve(solve,0,w,0,h);

    return res;
}
//
template<class F>
ll monge_d_edge_shortest(F&f,int n,int d,ll inf=2e13){
    ll ac=-inf,wa=inf;
    auto get=[&](ll wj){
        using P=pair<ll,int>;
        vc<P>dp(n,P{1e18,1e9});
        dp[0]={0,0};
        auto dfs=[&](auto&dfs,int l,int r)->void{
            if(l+1==r)return;
            int mid=l+r>>1;
            dfs(dfs,l,mid);
            auto F2=[&](int i,int j)->P{
                i+=mid;
                j+=l;
                return P{f(j,i)+dp[j].first+wj,dp[j].second-1};
            };
            //j to i 
            auto R=monotone_minima<P,decltype(F2)>(F2,r-mid,mid-l,0);
            rep(i,R.size()){
                chmin(dp[i+mid],R[i]);
            }
            dfs(dfs,mid,r);
        };
        dfs(dfs,0,n);
        if(wj==0)dbg(dp);
        return dp.back();
    };
    while(wa-ac>1){
        ll wj=ac+wa>>1;
        if(-get(wj).second>=d)ac=wj;
        else wa=wj;
    }
    return get(ac).first-ac*d;
}

template<class F>
pair<ll,ll> monge_edge_shortest2(F&f,int n){
    auto get=[&](){
        using P=pair<ll,int>;
        vc<P>dp(n,P{1e18,1e9});
        dp[0]={0,0};
        auto dfs=[&](auto&dfs,int l,int r)->void{
            if(l+1==r)return;
            int mid=l+r>>1;
            dfs(dfs,l,mid);
            auto F2=[&](int i,int j)->P{
                i+=mid;
                j+=l;
                return P{f(j,i)+dp[j].first,dp[j].second+1};
            };
            //j to i 
            auto R=monotone_minima<P,decltype(F2)>(F2,r-mid,mid-l,0);
            rep(i,R.size()){
                chmin(dp[i+mid],R[i]);
            }
            dfs(dfs,mid,r);
        };
        dfs(dfs,0,n);
        return dp.back();
    };
    auto res=get();
    return res;
}