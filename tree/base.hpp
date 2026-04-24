#pragma once
#include"../template.hpp"
#include"../graph/base.hpp" 
struct Tree{
    using Graph=static_graph<1>;
    mutable Graph g;
    mutable bool built_hld=false;
    int n;
    mutable vc<int>in,out,head,size_,par,depth,ord;
    Tree(int n):n(n),g(n,2*(n-1)){}
    void add_edge(int a,int b){
        assert(0<=a&&a<n&&0<=b&&b<n);
        g.add_edge(a,b);
        g.add_edge(b,a);
    }
    bool is_to_par(auto&e)const{
        return par[e.from]==e.to;
    }
    int size()const{
        return n;
    }
    auto operator[](int u)const{
        return g[u];
    }
    auto operator[](int u){
        return g[u];
    }
    template<int substract>
    void input(){
        rep(i,n-1){
            INT(a,b);
            a-=substract;
            b-=substract;
            g.add_edge(a,b);
            g.add_edge(b,a);
        }
    }
    void build(int root=0)const{
        if(built_hld)return;
        built_hld=1;
        in.resize(n);
        out.resize(n);
        head.resize(n);
        size_.resize(n,1);
        par.resize(n);
        depth.resize(n);
        ord.clear();
        ord.reserve(n);
        par[root]=-1;
        head[root]=root;
        int T=0;
        auto dfs=[&](auto&dfs,int u,int v,int d)->void{
            depth[u]=d++;
            auto s=g[u];
            int heavy=-1,par_id=-1;
            rep(i,s.size()){
                auto&e=s[i];
                if(e.to==v){
                    par_id=i;
                    continue;
                }
                par[e.to]=u;
                dfs(dfs,e.to,u,d);
                size_[u]+=size_[e.to];
                if(heavy==-1||size_[s[heavy].to]<size_[e.to])heavy=i;
            }
            if(heavy!=-1&&heavy!=0){
                swap(s[heavy],s[0]);
                if(par_id==0)par_id=heavy;
                else if(par_id==heavy)par_id=0;
            }
            if(par_id!=-1&&par_id+1!=s.size()){
                swap(s[par_id],s[s.size()-1]);
            }
        };dfs(dfs,root,-1,0);
        {auto dfs=[&](auto&dfs,int u)->void{
            in[u]=T++;
            ord.push_back(u);
            auto s=g[u];
            bool first=true;
            for(auto&e:s)if(e.to!=par[u]){
                head[e.to]=first?head[u]:e.to;
                first=false;
                dfs(dfs,e.to);
            }
            out[u]=T;
        };dfs(dfs,root);}
    }
    auto heavy_edge(int u)const{
        build();
        auto s=g[u];
        int sz=s.size(),ce=(u==ord[0]?sz:sz-1);
        if(ce<=0)return span<const Graph::edge>{s.l,s.l};
        return span<const Graph::edge>{s.l,s.l+1};
    }
    auto light_edges(int u)const{
        build();
        auto s=g[u];
        int sz=s.size(),ce=(u==ord[0]?sz:sz-1);
        if(ce<=1)return span<const Graph::edge>{s.l,s.l};
        return span<const Graph::edge>{s.l+1,s.l+ce};
    }
    int lca(int a,int b)const{
        build();
        while(1){
            if(head[a]==head[b]){
                if(depth[a]<depth[b])return a;
                return b;
            }
            if(depth[head[a]]<depth[head[b]])swap(a,b);
            a=par[head[a]];
        }
    }
    int dist(int a,int b)const{
        build();
        return depth[a]+depth[b]-2*depth[lca(a,b)];
    }
    int jumpup(int a,int k)const{
        build();
        if(k<0||depth[a]<k)return -1;
        while(k>0){ 
            if(in[a]-in[head[a]]>=k){
                return ord[in[a]-k];
            }
            k-=(in[a]-in[head[a]]+1);
            a=par[head[a]];
        }
        return a;
    }
    int jump(int s,int t,int k)const{
        build();
        int L=lca(s,t);
        int D=depth[s]+depth[t]-2*depth[L];
        if(depth[s]-depth[L]>=k){
            return jumpup(s,k);
        }else{
            return jumpup(t,D-k);
        }
    }   
    vc<pair<int,int>>Query(int s,int t)const{
        build();
        vc<pair<int,int>>rs,rt;
        while(head[s]!=head[t]){
            if(depth[head[s]]>depth[head[t]]){
                rs.push_back({in[s],in[head[s]]});
                s=par[head[s]];
            }else{
                rt.push_back({in[head[t]],in[t]});
                t=par[head[t]];
            }
        }
        if(depth[s]>depth[t]){
            rs.push_back({in[s],in[t]});
        }else{
            rt.push_back({in[s],in[t]});
        }
        reverse(rt.begin(),rt.end());
        rs.reserve(rs.size()+rt.size());
        for(auto&x:rt)rs.push_back(x);
        return rs;
    }
    pair<int,int>get_diameter()const{
        auto find_farthest=[&](int from)->int{
            vc<int>md(n,1e9);
            md[from]=0;
            auto dfs=[&](auto&dfs,int u)->void{
                for(auto&e:g[u]){
                    if(chmin(md[e.to],md[u]+1))dfs(dfs,e.to);
                }
            };
            dfs(dfs,from);
            return max_element(all(md))-md.begin();
        };
        int v1=find_farthest(0);
        int v2=find_farthest(v1);
        return {v1,v2};
    }
};
