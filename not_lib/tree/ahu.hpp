#include"../../template.hpp"
#include"../../graph/base.hpp"
#include"../../tree/base.hpp"
#include"../../string/lcpsuf.hpp"
string ahu(const Tree&tree_,int root){
    static_graph<1>g(tree_.size());
    Tree tree(tree_.size(),g);
    rep(i,tree_.size())for(auto&x:tree_[i])if(i<x.to)tree.add_edge(i,x.to);
    tree.build(root);
    vvc<int>levels(tree.size());
    vc<int>level(tree.size());
    auto dfs=[&](auto&dfs,int u,int v,int d)->void{
        for(auto&e:tree[u]){
            if(e.to==v)continue;
            dfs(dfs,e.to,u,d+1);
        }
        levels[d].push_back(u);
        level[u]=d;
        return;
    };
    dfs(dfs,root,-1,0);
    vvc<pair<int,int>>sorts(tree.size(),vc<pair<int,int>>{{0,0}});
    vc<int>val(tree.size());
    vvvc<int>vals(tree.size());
    while(levels.back().empty()){
        levels.pop_back();
        vals.pop_back();
    }
    vals.back()=vvc<int>(1);
    for(auto&x:levels.back()){
        val[x]=1;
        vals.back()[0].push_back(x);
    }
    drep(i,(int)levels.size()-1){
        rep(j,vals[i+1].size()){
            for(auto&x:vals[i+1][j])sorts[tree.par[x]].pb({x,j+1});
        }
        vc<int>send_sf;
        vc<int>start;
        int sep=-1;
        for(auto&x:levels[i]){
            start.pb(x);
            send_sf.pb(sorts[x][0].second);
            REP(k,1,sorts[x].size()){
                start.pb(-1);
                send_sf.pb(sorts[x][k].second);
            }
            start.pb(-1);
            send_sf.pb(sep--);
        }
        vc<int>ord;
        auto SF=sf_array(send_sf);
        for(auto&x:SF){
            if(start[x]>=0){
                ord.push_back(start[x]);
            }
        }
        int id=1;
        vals[i].push_back({});
        rep(j,ord.size()){
            val[ord[j]]=id;
            vals[i].back().push_back(ord[j]);
            if(j+1==ord.size())break;
            auto is_same_nxt=[&]()->bool{
                if(sorts[ord[j]].size()!=sorts[ord[j+1]].size())return 0;
                rep(k,sorts[ord[j]].size()){
                    if(sorts[ord[j]][k].second!=sorts[ord[j+1]][k].second)return 0;
                }
                return 1;
            };
            if(!is_same_nxt()){
                ++id;
                vals[i].push_back({});
            }
        }
    }
    string s;
    auto dfs2=[&](auto&dfs2,int u,int v)->void{
        s+='(';
        REP(j,1,sorts[u].size()){
            auto&x=sorts[u][j];
            if(x.first==v)continue;
            dfs2(dfs2,x.first,u);
        }
        s+=')';
    };
    dfs2(dfs2,root,-1);
    //so=sorts;
    return s;
}