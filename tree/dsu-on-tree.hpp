#pragma once
template<class Tree>
struct DsuOnTree{
    Tree&g;
    DsuOnTree(Tree&g):g(g){}
    template<class Add,class Query,class Reset>
    void run(Add add,Query query,Reset reset,int root=0){
        g.build(root);
        auto dfs=[&](auto&dfs,int u,int v,int keep,int do_query)->void{
            if(do_query){
                for(auto e:g.light_edges(u)){
                    dfs(dfs,e.to,u,0,1);
                }
            }
            for(auto e:g.heavy_edge(u)){
                dfs(dfs,e.to,u,1,do_query);
            }
            for(auto e:g.light_edges(u)){
                dfs(dfs,e.to,u,1,0);
            }
            add(u);
            if(do_query)query(u);
            if(keep==0)reset();
        };
        dfs(dfs,root,-1,0,1);
    }
};