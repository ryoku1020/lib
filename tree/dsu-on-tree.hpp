#pragma once
template<class tree>
struct dsu_on_tree{
    tree&g;
    dsu_on_tree(tree&g):g(g){}
    template<class add_func,class query_func,class reset_func>
    void run(add_func add,query_func query,reset_func reset,int root=0){
        assert(0<=root&&root<g.size());
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
