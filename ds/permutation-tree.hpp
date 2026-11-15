#pragma once
#include"../template.hpp"
#include"segment_tree/segtree.hpp"
#include"monoid/min.hpp"
#include"monoid/max.hpp"
namespace ryoku{
struct permutation_tree{
    vc<int>p;
    permutation_tree(vc<int>p):p(move(p)){build();}
    enum nodetype{
        linear_inc,linear_dec,prime,leaf
    };
    struct Node{
        nodetype type;
        int l,r;
        vc<int>child;
        int is_prime()const{return type==prime;}
        int is_linear()const{return type==linear_inc||type==linear_dec;}
        int is_linearinc()const{return type==linear_inc;}
        int is_lineardec()const{return type==linear_dec;}
    };
    vc<Node>nodes;
    int root;
    void build(){
        int n=p.size();
        nodes.clear();
        if(n==0){root=-1;return;}
        vc<pii>maybestrong;
        {
            vc<int>inv(n);rep(i,n)inv[p[i]]=i;
            segtree<Min<int>>minseg(p);
            segtree<Max<int>>maxseg(p);
            segtree<Max<int>>seginv(inv);
            vc<int>ls;
            rep(r,n){
                int y=r;
                while(ls.size()){
                    auto pl=ls.back();
                    ll minv=minseg.prod(pl,r+1);
                    ll maxv=maxseg.prod(pl,r+1);
                    ll is_good=(maxv-minv-(r-pl))==0;
                    if(is_good){
                        y=pl;
                        maybestrong.pb({y,r});
                        ls.pop_back();
                    }else{
                        if(seginv.prod(minv,maxv)>r){
                            break;
                        }else{
                            ls.pop_back();
                        }
                    }
                }
                ls.pb(y);
            }
        }
        nodes.reserve(n+maybestrong.size());
        {
            vc<pii>List(n);
            rep(i,n){
                List[i]={i,i+1};
                nodes.pb({leaf,(int)i,(int)i,{}});
            }
            sort(all(maybestrong),[](auto a,auto b){
                return a.se-a.fi<b.se-b.fi;
            });
            for(auto[l,r]:maybestrong){
                Node here{prime,l,r,{}};
                for(int j=l;j<=r;j=List[j].se){
                    here.child.pb(List[j].fi);
                }
                nodes.pb(move(here));
                List[l]={int(nodes.size())-1,r+1};
            }
        }
        vc<pii>().swap(maybestrong);
        REP(i,n,nodes.size()){
            int inc=1,dec=1;
            auto&child=nodes[i].child;
            REP(j,1,child.size()){
                int a=p[nodes[child[j-1]].l];
                int b=p[nodes[child[j]].l];
                inc&=a<b;
                dec&=a>b;
            }
            nodes[i].type=inc?linear_inc:dec?linear_dec:prime;
        }
        vc<Node>true_node;
        true_node.reserve(nodes.size());
        auto dfs=[&](auto&dfs,int u)->int{
            const Node&node=nodes[u];
            if(node.child.empty()){
                int id=true_node.size();
                true_node.pb(node);
                return id;
            }
            if(node.type!=prime&&nodes[node.child[0]].type==node.type){
                int id=dfs(dfs,node.child[0]);
                chmin(true_node[id].l,node.l);
                chmax(true_node[id].r,node.r);
                REP(i,1,node.child.size()){
                    int v=dfs(dfs,node.child[i]);
                    true_node[id].child.pb(v);
                }
                return id;
            }else{
                int id=true_node.size();
                true_node.pb({node.type,node.l,node.r,{}});
                for(int v:node.child){
                    int w=dfs(dfs,v);
                    true_node[id].child.pb(w);
                }
                return id;
            }
        };
        root=dfs(dfs,int(nodes.size())-1);
        nodes=move(true_node);
    }
    int size()const{
        return nodes.size();
    }
};
}
