#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class Info>
struct formatter<segtree<Info>>{
    static void print(ostream&os,const segtree<Info>&seg){
        os<<"segtree [n="<<seg.N<<"]\n\n";
        internal::print_index_values(os,seg.N,[&](size_t i)->const auto&{return seg.node[seg.n+i];});
    }
};
namespace internal{
template<class Info>
struct raw_formatter<segtree<Info>>{
    static void print(ostream&os,const segtree<Info>&seg){
        os<<"segtree raw n="<<seg.N<<" size="<<seg.n<<"\nnode = ";
        print_value(os,seg.node,0);
    }
};
}
namespace internal{
template<class Info>
struct tree_formatter<segtree<Info>>{
    static void print(ostream&os,const segtree<Info>&seg){
        os<<"segtree [n="<<seg.N<<"]\n";
        size_t shown=0;
        bool truncated=false;
        auto dfs=[&](auto&dfs,int k,int l,int r,string prefix,bool last,bool root)->void{
            if(l>=seg.N)return;
            if(shown>=config.max_tree_nodes){truncated=true;return;}
            shown++;
            os<<'\n'<<prefix;
            if(!root)os<<(last?"└─ ":"├─ ");
            os<<'['<<l<<','<<min(r,seg.N)<<") = ";
            print_value(os,seg.node[k],0);
            if(k<seg.n&&min(r,seg.N)-l>1){
                int m=(l+r)/2;
                string child_prefix=prefix+(root?"":last?"   ":"│  ");
                bool has_right=m<seg.N;
                dfs(dfs,k*2,l,m,child_prefix,!has_right,false);
                if(has_right)dfs(dfs,k*2+1,m,r,child_prefix,true,false);
            }
        };
        if(seg.N)dfs(dfs,1,0,seg.n,"",true,true);
        if(truncated)os<<"\n…";
    }
};
}
}
