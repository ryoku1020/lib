#pragma once
optional<vc<pair<int,int>>>havel_hakimi(vc<int>d){
    int n=d.size();
    if(n==0)return vc<pair<int,int>>{};
    if(max(d)>n-1||min(d)<0)return nullopt;
    int now_front=n;
    vc<pair<int,int>>ans;
    vvc<int>is(n+1);
    rep(i,n)is[d[i]].pb(i);
    while(now_front>0){
        if(is[now_front].empty()){
            now_front--;
            continue;
        }
        auto target=is[now_front].back();is[now_front].pop_back();
        int need=now_front;
        vc<pair<int,int>>tmp;
        while(tmp.size()<need){
            while(now_front>0&&is[now_front].empty()){
                now_front--;
            }
            if(now_front==0)return nullopt;
            tmp.push_back({is[now_front].back(),now_front-1});is[now_front].pop_back();
        }
        for(auto&x:tmp){
            ans.push_back({target,x.first});
            is[x.second].push_back(x.first);
        }
        now_front=need;
    }
    return ans;
}
