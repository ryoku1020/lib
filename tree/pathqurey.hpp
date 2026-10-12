
#pragma once
#include"base.hpp"
#include"../ds/segment_tree/segtree.hpp"
#include"../ds/segment_tree/lazy-segtree.hpp"
namespace ryoku{
template<class info>
struct pathquery_info{
    using T=typename info::value_type;
    using value_type=pair<T,T>;
    static value_type id(){return {info::id(),info::id()};}
    static value_type op(const value_type&a,const value_type&b){
        return {info::op(a.first,b.first),info::op(b.second,a.second)};
    }
};
template<class acted>
struct pathquery_acted{
    using info=pathquery_info<typename acted::info>;
    using tag=typename acted::tag;
    using value_type=typename info::value_type;
    using lazy_type=typename acted::lazy_type;
    static value_type act(value_type x,lazy_type f,int len){
        return {acted::act(x.first,f,len),acted::act(x.second,f,len)};
    }
};
template<class info,int is_edge,class Seg>
struct pathquery_base{
    using value_type=typename info::value_type;
    tree<unweighted>g;
    Seg seg;
    pathquery_base(const tree<unweighted>&g,int root=0):g(g),seg(g.size()){
        this->g.build(root);
    }
    void set_vertex(int v,value_type val){
        seg.set(g.in[v],{val,val});
    }
    void set_edge(int child,value_type val){
        assert(g.par[child]!=-1);
        set_vertex(child,val);
    }
    value_type get_vertex(int v){
        return seg.prod(g.in[v],g.in[v]+1).first;
    }
    value_type get_edge(int child){
        assert(g.par[child]!=-1);
        return get_vertex(child);
    }
    value_type query(int a,int b){
        value_type res=info::id();
        for(auto [l,r]:g.query(a,b,is_edge)){
            auto x=seg.prod(min(l,r),max(l,r)+1);
            res=info::op(res,l<=r?x.first:x.second);
        }
        return res;
    }
};
template<class info,int is_edge>
struct pathquery:pathquery_base<info,is_edge,segtree<pathquery_info<info>>>{
    using base=pathquery_base<info,is_edge,segtree<pathquery_info<info>>>;
    using base::base;
};
template<class acted,int is_edge>
struct lazy_pathquery:pathquery_base<typename acted::info,is_edge,lazy_segtree<pathquery_acted<acted>>>{
    using base=pathquery_base<typename acted::info,is_edge,lazy_segtree<pathquery_acted<acted>>>;
    using base::base;
    using lazy_type=typename acted::lazy_type;
    void apply_vertex(int v,lazy_type f){
        this->seg.applyat(this->g.in[v],f);
    }
    void apply_edge(int child,lazy_type f){
        assert(this->g.par[child]!=-1);
        apply_vertex(child,f);
    }
    void apply(int a,int b,lazy_type f){
        for(auto [l,r]:this->g.query(a,b,is_edge)){
            this->seg.apply(min(l,r),max(l,r)+1,f);
        }
    }
};
}
