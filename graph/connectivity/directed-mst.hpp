#pragma once
#include"../../ds/utility/noninfo.hpp"
#include"../../ds/utility/node-pool.hpp"
#include"../../ds/union_find/uf.hpp"
template<class T,class DATA=noninfo>
struct skew_heap{
    struct Node{
        Node*l,*r;
        T val;
        T lazy;
        DATA data;
        void push(){
            if(l)l->apply(lazy);
            if(r)r->apply(lazy);
            lazy=0;
        }
        void apply(T x){
            val+=x;
            lazy+=x;
        }
    };
    static node_pool<Node>node;
    static Node*getnew(){
         Node*res=node.alloc();
         res->l=res->r=0;
         res->val=T(),res->data=DATA();
         res->lazy=T();
         return res;
    }
    static Node*meld(Node*a,Node*b){
        if(a==0)return b;
        if(b==0)return a;
        if(a->val>b->val)swap(a,b);
        a->push();
        a->r=meld(a->r,b);
        swap(a->l,a->r);
        return a;
    }
    static Node*push(Node*root,T x,DATA data){
        Node*R=getnew();R->val=x,R->data=data;
        return meld(root,R);
    }
    static pair<pair<T,DATA>,Node*>pop(Node*root){
        assert(root);
        root->push();
        auto res=pair<T,DATA>(root->val,root->data);
        return{res,meld(root->l,root->r)};
    }
    static Node*add(Node*root,T x){
        if(root)root->apply(x);
        return root;
    }
};
template<class T,class DATA>
node_pool<typename skew_heap<T,DATA>::Node>skew_heap<T,DATA>::node;
template<class Graph>
vc<typename Graph::edge>directed_mst(Graph g,int root){
    int N=g.size();
    using Heap=skew_heap<ll,int>;
    int MAX=2*N+5;
    vc<Heap::Node*>inner_edge(MAX);
    rep(i,N)for(auto&e:g[i]){
        inner_edge[e.to]=Heap::push(inner_edge[e.to],e.cost,e.id);
    }
    disjoint_set_union dsu(MAX);
    vc<int>used(MAX);
    vc<int>par(MAX,-1);
    vc<int>rt(MAX);rep(i,MAX)rt[i]=i;
    used[root]=2;
    vc<pll>best(MAX);
    int bb=N;
    rep(i,N){
        if(used[i])continue;
        vc<int>path;
        int v=i;
        while(1){
            path.pb(v);used[v]=1;
            while(inner_edge[v]){
                if(dsu.same(v,g.get_edge(inner_edge[v]->data).from)){
                    inner_edge[v]=Heap::pop(inner_edge[v]).se;
                }else break;
            }
            if(!inner_edge[v]){
                return{};
            }
            auto [ced,hp]=Heap::pop(inner_edge[v]);inner_edge[v]=hp;
            auto cost=ced.fi;
            auto eid=ced.se;
            int from=rt[dsu.root(g.get_edge(eid).from)];

            best[v]={cost,eid};
            if(used[from]==2){
                break;
            }
            if(used[from]==0){
                v=from;
                continue;
            }
            while(1){
                int K=path.back();path.pop_back();
                inner_edge[K]=Heap::add(inner_edge[K],-best[K].fi);
                inner_edge[bb]=Heap::meld(inner_edge[bb],inner_edge[K]);
                par[K]=bb;
                dsu.merge(K,bb);
                used[K]=2;
                if(K==from)break;
            }
            rt[dsu.root(bb)]=bb;
            v=bb;
            bb++;
        }
        for(auto&x:path){
            used[x]=2;
        }
    }
    vc<int>done(bb);done[root]=1;
    vc<typename Graph::edge>ans;
    drep(i,bb){
        if(done[i])continue;
        int eid=best[i].se;
        ans.pb(g.get_edge(eid));
        for(int v=g.get_edge(eid).to;v!=-1&&!done[v];v=par[v])done[v]=1;
    }
    return ans;
}