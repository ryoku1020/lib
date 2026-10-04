#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class Info,class Size,bool Persistent>
struct formatter<dynamic_segtree<Info,Size,Persistent>>{
    static void print(ostream&os,const dynamic_segtree<Info,Size,Persistent>&seg){
        os<<"dynamic_segtree size="<<seg.N<<" persistent="<<(Persistent?"true":"false")
          <<" (use debug::version(seg, root) to inspect a root)";
    }
};
template<class Info,class Size,bool Persistent>
struct formatter<version_view<dynamic_segtree<Info,Size,Persistent>,typename dynamic_segtree<Info,Size,Persistent>::node*>>{
    using seg_type=dynamic_segtree<Info,Size,Persistent>;
    using node=typename seg_type::node;
    static void print(ostream&os,const version_view<seg_type,node*>&view){
        os<<"dynamic_segtree root size="<<view.value.N<<"\nreachable nodes";
        size_t shown=0;
        bool truncated=false;
        auto dfs=[&](auto&dfs,node*now,Size l,Size r)->void{
            if(!now)return;
            if(shown>=config.max_tree_nodes){truncated=true;return;}
            shown++;
            os<<"\n  ["<<l<<','<<r<<") = ";internal::print_value(os,now->val,0);
            if(r-l>1){Size mid=(l+r)>>1;dfs(dfs,now->l,l,mid);dfs(dfs,now->r,mid,r);}
        };
        dfs(dfs,view.root,0,view.value.N);
        if(truncated)os<<"\n  …";
    }
};
}
