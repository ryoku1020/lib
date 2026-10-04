#pragma once
#include "../local.hpp"
namespace debug{
using namespace ryoku;
template<class acted,bool Beats>
struct formatter<lazy_segtree<acted,Beats>>{
    static void print(ostream&os,const lazy_segtree<acted,Beats>&seg){
        auto copy=seg;
        os<<"lazy_segtree [n="<<seg.N<<"]\n\n";
        internal::print_index_values(os,copy.N,[&](size_t i){return copy.prod(i,i+1);});
    }
};
namespace internal{
template<class acted,bool Beats>
struct raw_formatter<lazy_segtree<acted,Beats>>{
    static void print(ostream&os,const lazy_segtree<acted,Beats>&seg){
        os<<"lazy_segtree raw n="<<seg.N<<" size="<<seg.n<<"\nnode = ";
        print_value(os,seg.node,0);
        os<<"\nlazy = ";print_value(os,seg.lazy,0);
    }
};
}
namespace internal{
template<class acted,bool Beats>
struct tree_formatter<lazy_segtree<acted,Beats>>{
    static void print(ostream&os,const lazy_segtree<acted,Beats>&seg){
        os<<"lazy_segtree [n="<<seg.N<<"]\n";
        size_t shown=0;
        bool truncated=false;
        using tag=typename lazy_segtree<acted,Beats>::tag;
        using lazy_type=typename lazy_segtree<acted,Beats>::lazy_type;
        auto dfs=[&](auto&dfs,int k,int l,int r,lazy_type inherited,string prefix,bool last,bool root)->void{
            if(l>=seg.N)return;
            if(shown>=config.max_tree_nodes){truncated=true;return;}
            shown++;
            os<<'\n'<<prefix;
            if(!root)os<<(last?"└─ ":"├─ ");
            os<<'['<<l<<','<<min(r,seg.N)<<") value=";
            print_value(os,acted::act(seg.node[k],inherited,seg.len[k]),0);
            if(k<seg.n){os<<"  lazy=";print_value(os,seg.lazy[k],0);}
            if(k<seg.n&&min(r,seg.N)-l>1){
                int m=(l+r)/2;
                string child_prefix=prefix+(root?"":last?"   ":"│  ");
                bool has_right=m<seg.N;
                auto child_lazy=tag::op(seg.lazy[k],inherited);
                dfs(dfs,k*2,l,m,child_lazy,child_prefix,!has_right,false);
                if(has_right)dfs(dfs,k*2+1,m,r,child_lazy,child_prefix,true,false);
            }
        };
        if(seg.N)dfs(dfs,1,0,seg.n,tag::id(),"",true,true);
        if(truncated)os<<"\n…";
    }
};
}
}
