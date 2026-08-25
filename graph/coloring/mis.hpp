
template<class G>
vc<int>mis(G g){
    int n=g.size();
    vc<int>used(n);
    vc<int>deg(n);rep(i,n)deg[i]=g[i].size();
    vvc<int>has(n,vc<int>(n));rep(i,n)for(auto&e:g[i])has[i][e.to]=has[e.to][i]=1;
    vc<int>ans;
    auto dfs=[&](auto&dfs,vc<int>active)->void{
        if(ans.size()<active.size()){
            ans=active;
        }
        rep(i,n){
            if(!used[i]&&deg[i]<=1){
                active.pb(i);
                used[i]++;
                rep(j,n)if(has[i][j]){
                    deg[j]--,used[j]++;
                    if(used[j]==1)rep(k,n)if(has[j][k]){
                        deg[k]--;
                    }
                }
                dfs(dfs,active);

                rep(j,n)if(has[i][j]){
                    deg[j]++,used[j]--;
                    if(used[j]==0)rep(k,n)if(has[j][k]){
                        deg[k]++;
                    }
                }
                used[i]--;
                active.pop_back();
                return;
            }
        }
        pii arm{-1,-1};
        rep(i,n){
            if(!used[i]){
                chmax(arm,pii{deg[i],i});
            }
        }
        if(arm.first!=-1){
            rep(j,n)if(has[arm.second][j])deg[j]--;
            used[arm.second]=1;
            dfs(dfs,active);
            active.pb(arm.second);
            rep(j,n){
                if(has[arm.second][j]){
                    used[j]++;
                    if(used[j]==1)rep(k,n){
                        if(has[j][k]){
                            deg[k]--;
                        }
                    }
                }
            }
            dfs(dfs,active);
            rep(j,n){
                if(has[arm.second][j]){
                    used[j]--;
                    if(used[j]==0)rep(k,n){
                        if(has[j][k]){
                            deg[k]++;
                        }
                    }
                }
            }
            active.pop_back();
            used[arm.second]=0;
            rep(j,n)if(has[arm.second][j])deg[j]++;
        }
    };  
    dfs(dfs,{});
    return ans;
}
