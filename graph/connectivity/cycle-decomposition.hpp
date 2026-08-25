
vvc<int>cycle_decomposition(vc<int>p){
    int n=p.size();
    vc<int>seen(n);
    vvc<int>res;
    rep(i,n){
        if(!seen[i]){
            seen[i]=1;res.pb({(int)i});
            int now=i;
            while(1){
                now=p[now];if(now==i)break;
                seen[now]=1;res.back().pb(now);
            }
        }
    }
    return res;
}