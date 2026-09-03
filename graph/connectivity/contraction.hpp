#pragma once
template<class G>
pair<G,vc<int>>contraction(G g,vc<int>group){
    map<int,int>mp;
    int id=0;
    for(auto&x:group){
        if(!mp.count(x))mp[x]=id++;
        x=mp[x];
    }
    G res(id);
    rep(i,g.size()){
        for(auto&e:g[i]){
            if(G::directed()==false&&i>e.to)continue;
            res.add_edge(group[i],group[e.to],e.cost);
        }
    }
    return {res,group};
}