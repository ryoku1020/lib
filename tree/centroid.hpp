#pragma once
#include"../template.hpp"
template<class F1,class F2>
void internal_centroid_decomposition13(vvc<int>&g,vc<int>&is_virtual,vc<int>&is_alive,vc<int>&size,int root,vvc<int>&send,vc<int>&col,F1&Callnonvirtual,F2&Callvirtual){
    vc<int>alives;
    int non_virtual=0;
    auto dfs_first=[&](auto&dfs_first,int u,int v)->void{
        alives.push_back(u);
        size[u]=1;
        non_virtual+=!is_virtual[u];
        for(auto&e:g[u]){
            if(!is_alive[e])continue;
            if(e==v)continue;
            send[u].pb(e);
            send[e].pb(u);
            dfs_first(dfs_first,e,u);
            size[u]+=size[e];
        }
    };
    dfs_first(dfs_first,root,-1);
    
    if(non_virtual==0){
        for(auto&x:alives)send[x].clear();
        return;
    }
    int centroid=-1;
    for(auto&x:alives){
        bool is_centroid=1;
        for(auto&e:g[x]){
            if(!is_alive[e])continue;
            if(size[x]<size[e])continue;
            if(size[e]>size[root]/2)is_centroid=0;
        }
        if(size[root]-size[x]>size[root]/2)is_centroid=0;
        if(is_centroid)centroid=x;
    }
    if(is_virtual[centroid]){
        vc<pii>hist;
        int c0size=0,c1size=0;
        for(auto&e:g[centroid]){
            if(!is_alive[e])continue;
            int target=c0size>c1size;
            auto dfs=[&](auto&dfs,int u,int v)->void{
                hist.pb({u,col[u]});
                col[u]=target;(target?c1size:c0size)++;
                for(auto&e:g[u]){ 
                    if(!is_alive[e])continue;
                    if(e==v)continue;
                    dfs(dfs,e,u);
                }
            };
            dfs(dfs,e,centroid);
        }
    
        Callvirtual(centroid,col,send,is_virtual);
        for(auto&x:alives)send[x].clear();
        for(auto&x:alives)if( col[x])is_alive[x]=0;
        is_alive[centroid]=1;
        auto GCFIRST=g[centroid];g[centroid].clear();
        for(auto&x:GCFIRST)if(!col[x])g[centroid].pb(x);
        internal_centroid_decomposition13<F1,F2>(g,is_virtual,is_alive,size,centroid,send,col,Callnonvirtual,Callvirtual);
        for(auto&x:alives)if( col[x])is_alive[x]=1;
        for(auto&x:alives)if(!col[x])is_alive[x]=0;
        is_alive[centroid]=1;
        g[centroid].clear();
        for(auto&x:GCFIRST)if(col[x]==1)g[centroid].pb(x);
        internal_centroid_decomposition13<F1,F2>(g,is_virtual,is_alive,size,centroid,send,col,Callnonvirtual,Callvirtual);
        g[centroid]=move(GCFIRST);
        for(auto&x:alives)if(!col[x])is_alive[x]=1;
        for(auto&[a,b]:hist)col[a]=b;
    }else{
        Callnonvirtual(centroid,send,is_virtual);
        for(auto&x:alives)send[x].clear();
        is_virtual[centroid]=1;
        internal_centroid_decomposition13<F1,F2>(g,is_virtual,is_alive,size,centroid,send,col,Callnonvirtual,Callvirtual);
        is_virtual[centroid]=0;
    }
}
//copy して受け取ると死ぬので注意！！！
template<class F1,class F2>
void centroid_decomposition13(vvc<int>&g,F1&Callnonvirtual,F2&Callvirutal){
    int n=g.size();
    vc<int>is_virtual(n);
    vc<int>is_alive(n,1);
    vc<int>size(n);
    vvc<int>send(n);
    vc<int>col(n);
    internal_centroid_decomposition13<F1,F2>(g,is_virtual,is_alive,size,0,send,col,Callnonvirtual,Callvirutal);
}
//copy して受け取ると死ぬので注意！！！
template<class Tree,class F1,class F2>
void centroid_decomposition13(Tree&g,F1&Callnonvirtual,F2&Callvirutal){
    int n=g.size();
    vvc<int>G(n);rep(i,n)for(auto&x:g[i]){
        G[i].pb(x.to);
    }
    centroid_decomposition13(G,Callnonvirtual,Callvirutal);
}   
