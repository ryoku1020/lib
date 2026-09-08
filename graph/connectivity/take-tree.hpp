#include"../lib/tree/base.hpp"
template<class T,class G>
tree<T>taketree(G g){
    vc<int>seen(g.size());
    tree<T>res(g.size());
    auto dfs=[&](auto&dfs,int u,int v)->void{
        for(auto&e:g[u]){
            if(!chmax(seen[e.to],1))continue;
            res.add_edge(e);
            dfs(dfs,e.to,u);
        }
    };
    rep(i,g.size())if(chmax(seen[i],1))dfs(dfs,i,-1);
    return res;
}