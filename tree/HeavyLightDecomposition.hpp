#pragma once
#include"../template.hpp"
#include"../graph/CompressedSparseRow.hpp"
struct HeavyLightDecomposition{
    CompressedSparseRowGraph gfirst,g;
    int n;
    vc<int>in,out,head,size,par,depth,ord;
    HeavyLightDecomposition(int n):n(n),gfirst(n),g(n),head(n,0),size(n,1),in(n),out(n),par(n,-1),depth(n){}
    void add_edge(int a,int b){
        gfirst.add_edge(a,b);
        gfirst.add_edge(b,a);
    }
    void build(){
        gfirst.build();
        ord.reserve(n);
        int T=0;
        auto dfs=[&](auto&dfs,int u,int v,int d)->void{
            depth[u]=d++;
            for(auto&x:gfirst[u]){
                if(x==v)continue;
                par[x]=u;
                g.add_edge(u,x);
                dfs(dfs,x,u,d);
                size[u]+=size[x];
            }
        };dfs(dfs,0,-1,0);
        g.build();
        {auto dfs=[&](auto&dfs,int u)->void{
            REP(i,1,g[u].size())if(size[g[u][i]]>size[g[u][0]])swap(g[u][i],g[u][0]);
            in[u]=T++;
            ord.push_back(u);
            for(auto&x:g[u])dfs(dfs,x);
            out[u]=T;
        };dfs(dfs,0);}
        {auto dfs=[&](auto&dfs,int u)->void{
            if(g[u].empty())return;
            head[g[u][0]]=head[u];
            REP(i,1,g[u].size())head[g[u][i]]=g[u][i];
            for(auto&x:g[u])dfs(dfs,x);
        };dfs(dfs,0);}
    }
    int lca(int a,int b){
        while(1){
            if(head[a]==head[b]){
                if(depth[a]<depth[b])return a;
                return b;
            }
            if(depth[head[a]]<depth[head[b]])swap(a,b);
            a=par[head[a]];
        }
    }
    int dist(int a,int b){
        return depth[a]+depth[b]-2*depth[lca(a,b)];
    }
    int jumpup(int a,int k){
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
    int jump(int s,int t,int k){
        int L=lca(s,t);
        int D=depth[s]+depth[t]-2*depth[L];
        if(depth[s]-depth[L]>=k){
            return jumpup(s,k);
        }else{
            return jumpup(t,D-k);
        }
    }   
    vc<pair<int,int>>Query(int s,int t){
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
};