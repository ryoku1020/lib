#include "template.hpp"
#include "ds/utility/Hash.hpp"
#include "math/modular/mod261.hpp"
#include "ds/sequence/Mo.hpp"
#include "ds/sequence/wavelet-matrix.hpp"
#include "ds/Reroot.hpp"
#include "ds/segment_tree/dynamic-lazy-segtree.hpp"
#include "ds/segment_tree/dynamic-segtree.hpp"
#include "ds/ordered/treap.hpp"
#include "ds/union_find/pot-uf.hpp"

struct rr_info{
    using V=int;
    using E=int;
    using edge=tree<unweighted>::edge;
    static E merge(E a,E b){return max(a,b);}
    static V put_vertex(E a,int){return a;}
    static E put_edge(V a,const edge&){return a+1;}
    static E id(){return 0;}
};

struct sum_info{
    using value_type=pair<ll,ll>;
    static value_type op(value_type a,value_type b){return {a.first+b.first,a.second+b.second};}
    static value_type e(){return {0,0};}
};

struct add_tag{
    using lazy_type=ll;
    static sum_info::value_type apply(sum_info::value_type x,lazy_type f){return {x.first+x.second*f,x.second};}
    static lazy_type merge(lazy_type a,lazy_type b){return a+b;}
    static lazy_type id(){return 0;}
};

struct additive_group{
    using value_type=ll;
    static value_type op(value_type a,value_type b){return a+b;}
    static value_type inv(value_type a){return -a;}
    static value_type e(){return 0;}
};

int main(){
    using H=hash_type<mod261_int,2>;
    H h=H::get_base();
    mo ord(1,1);
    ord.push(0,0);
    wm_base<int,4> wm;
    wm.build(vc<int>{1,2,3});
    int kth=wm.kth_smallest(0,3,1);
    redp<rr_info> dp(1);
    auto ans=dp.calc();
    dynamic_lazy_segtree<sum_info,add_tag,ll> seg(10,{0,1});
    seg.apply(0,3,2);
    auto sum=seg.prod(0,3).first;
    using dynamic_type=dynamic_segtree<sum_info,int,true>;
    dynamic_type dynamic_seg(10,{0,1});
    vc<dynamic_type::node*> roots{dynamic_seg.build()};
    roots.push_back(dynamic_seg.set(roots.back(),0,{1,1}));
    treap<sum_info,add_tag> tr(8);
    tr.build(vc<sum_info::value_type>{{1,1}});
    tr.apply(0,1,2);
    potentialized_union_find<additive_group> uf(2);
    uf.merge(0,1,5);
    return int(h[0].val())+kth+ans[0]+sum+tr.prod(0,1).first+uf.diff(0,1);
}
