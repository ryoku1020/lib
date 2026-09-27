#pragma once
template<class Graph>
pair<vc<int>,vc<int>>cycle_detection(const Graph&g){
    int n=g.size();
    vc<int>seen(n);
    vc<int>on(n);
    rep(i,n){
        if(seen[i])continue;
        vc<int>epath;
        vc<int>vpath;
        auto dfs=[&](auto&dfs,int u,int v,int eid)->pair<vc<int>,vc<int>>{
            on[u]=1;
            vpath.pb(u);
            for(auto&e:g[u]){
                if(seen[e.to]==1)continue;
                if(e.id==eid)continue;
                if(!on[e.to]){
                    epath.pb(e.id);
                    auto rs=dfs(dfs,e.to,u,e.id);
                    if(rs.first.size())return rs;
                    epath.pop_back();
                }else{
                    vc<int>res{};
                    vc<int>res2;
                    drep(i,vpath.size()){
                        res2.pb(vpath[i]);
                        if(vpath[i]==e.to)break;
                    }
                    DREP(i,(int)epath.size()-1,(int)epath.size()-(int)res2.size()+1){
                        res.pb(epath[i]);
                    }
                    reverse(all(res));reverse(all(res2));
                    res.pb(e.id);
                    return {res2,res};
                }
            }
            vpath.pop_back();
            on[u]=0;
            seen[u]=1;
            return {};
        };
        auto res=dfs(dfs,i,-1,-1);
        if(res.first.size())return res;
    }
    return {};
}
