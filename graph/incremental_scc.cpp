#pragma once
#include"base.cpp"
#include"scc.cpp"
#include"../ds/uf.cpp"
struct incremental_scc{
    int n;
    dsu dsu1;
    vc<int>id;
    vc<int>used;
    incremental_scc(int n=0):n(n),dsu1(n),id(n),used(n){}
    using graph=static_graph<1>;
    vc<graph::edge>es;
    vc<graph::edge>ans;
    void dfs(int l,int r,span<graph::edge>E){
        if(l>=r)return;
        int mid=l+r>>1;
        vc<int>roots;
        auto push=[&](int x){
            if(!used[dsu1.root(x)]){
                roots.push_back(dsu1.root(x));
                used[dsu1.root(x)]=1;
            }
        };
        auto unpush=[&](int x){
            used[dsu1.root(x)]=0;
        };
        for(auto&e:E){
            push(e.from),push(e.to);
        }
        rep(i,roots.size())id[roots[i]]=i;
        graph g(roots.size());
        for(auto&e:E){
            if(e.id>mid)continue;
            if(e.to==e.from)continue;
            int F=dsu1.root(e.from);
            int T=dsu1.root(e.to);
            assert(F!=T);
            g.add_edge(id[F],id[T]);
        }
        auto res=scc(g);
        vc<int>last(res.size(),-1);
        vc<pii>Merger;rep(i,res.size()){
            int L=last[res[i]];
            if(L!=-1&&!dsu1.same(roots[i],roots[L])){
                Merger.pb({roots[i],roots[L]});
            }
            last[res[i]]=i;
        }
        for(auto&e:E)unpush(e.to),unpush(e.from);
        auto it=partition(all(E),[&](const auto&e){
            return res[id[dsu1.root(e.to)]]==res[id[dsu1.root(e.from)]];
        });
        res.clear(); res.shrink_to_fit();
        last.clear(); last.shrink_to_fit();
        roots.clear(); roots.shrink_to_fit();
        dfs(l,mid,span<graph::edge>(E.data(),it-E.begin()));
        for(auto&x:Merger)dsu1.merge(x.first,x.second),ans.pb({x.first,x.second,mid});
        dfs(mid+1,r,span<graph::edge>(E.data()+(it-E.begin()),E.size()-(it-E.begin())));
    }
    int pushed=0;
    void push(int a,int b){
        es.pb({a,b,pushed++});
    }
    vc<graph::edge> work(){
        dfs(0,pushed,span<graph::edge>(es.data(),es.size()));
        return ans;
    }
};