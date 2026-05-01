#pragma once
#include"base.cpp"
//https://www.slideshare.net/slideshow/trianguler/38443802
template<template<bool,typename...>class G,typename T,typename F>
void enumerate_triangle(const G<0,T>&g,F f){
    static_assert(G<0,T>::directed()==false);
    G<1,T> new_graph(g.size(),g.m);
    int n=g.size();
    for(auto&e:g.all_edges()){
        if(pii{g.deg(e.from),e.from}>pii{g.deg(e.to),e.to})new_graph.add_edge(e.to,e.from);
        else new_graph.add_edge(e.from,e.to);
    }
    vc<int>vs(n);iota(all(vs),0);sort(all(vs),[&](auto a,auto b){
        return g.deg(a)<g.deg(b);
    });
    vc<int>seen(n);
    for(auto&i:vs){
        for(auto&e:new_graph[i]){
            seen[e.to]=1;
        }
        for(auto&e:new_graph[i]){
            for(auto&ne:new_graph[e.to]){
                if(seen[ne.to]){
                    f(i,e.to,ne.to);
                }  
            }
        }
        for(auto&e:new_graph[i]){
            seen[e.to]=0;
        } 
    }
}
