#define CP_NO_AUTO_ALL
#include "../../template.hpp"
#include "../../ds/segment_tree/segtree.hpp"
#include "../../ds/segment_tree/lazy-segtree.hpp"
#include "../../ds/segment_tree/assign-segtree.hpp"
#include "../../ds/segment_tree/dual-segtree.hpp"
#include "../../ds/segment_tree/dynamic-segtree.hpp"
#include "../../ds/segment_tree/dynamic-lazy-segtree.hpp"
#include "../../ds/segment_tree/segtree-2d.hpp"
#include "../../ds/sequence/BIT.hpp"
#include "../../ds/sequence/bit-vector.hpp"
#include "../../ds/sequence/wavelet-matrix.hpp"
#include "../../ds/persistent-array.hpp"
#include "../../ds/union_find/uf.hpp"
#include "../../ds/union_find/undo-uf.hpp"
#include "../../ds/union_find/pot-uf.hpp"
#include "../../ds/union_find/persistent-uf.hpp"
#include "../../graph/base.hpp"
#include "../../tree/base.hpp"
#include "../../graph/connectivity/lowlink.hpp"
#include "../../graph/network_flow/flow.hpp"
#include "../../graph/network_flow/min-cost-flow.hpp"
#include "../../ds/segment_tree/persistent-lazy-segtree.hpp"
#include "../../debug/local.hpp"

struct unprintable{int value;};
struct sum_info{
    using value_type=unprintable;
    static value_type op(value_type a,value_type b){return{a.value+b.value};}
    static value_type e(){return{};}
};
struct add_info{
    using value_type=ll;
    static value_type op(value_type a,value_type b){return a+b;}
    static value_type e(){return 0;}
};
struct add_tag{
    using lazy_type=ll;
    static lazy_type id(){return 0;}
    static ll apply(ll x,lazy_type add){return x+add;}
    static lazy_type merge(lazy_type a,lazy_type b){return a+b;}
};

struct printable_info{ll sum,mx;};
template<>
struct debug::formatter<printable_info>{
    static void print(ostream&os,const printable_info&x){
        os<<"{sum=";debug::print_value(os,x.sum);os<<", mx=";debug::print_value(os,x.mx);os<<'}';
    }
};

int main(){
    debug::config.color=false;
    int dbging=1;
    unprintable x{7};
    printable_info custom{3,5};
    assert(debug::to_string(x).find("<unprintable unprintable>")!=string::npos);
    assert(debug::to_string(vector<unprintable>{{1},{2}}).find("<unprintable unprintable>")!=string::npos);
    assert(debug::to_string(custom)=="{sum=3, mx=5}");
    assert(debug::to_string(bitset<8>(0b01001101))=="index: 01234567\nbit  : 10110010");
    vector<vector<int>>matrix{{0,100},{20,3}};
    dbg(1,"abc",string("abc"),vector<int>{1,2,3},matrix);
    dbg(make_pair(1,2),tuple<int,string>{3,"x"},optional<int>{4},variant<int,string>{"v"});
    bitset<8>bits(0b01001101);dbg(bits);
    dbg(x,vector<unprintable>{{1},{2}});
    dbg(custom);
    segtree<sum_info>seg(3,[&](int i){return unprintable{i+1};});
    dbg(seg);dbg(debug::tree(seg));
    lazy_segtree<add_info,add_tag>lazy(4,vector<ll>{1,2,3,4});
    lazy.apply(1,4,10);dbg(lazy);dbg(debug::raw(lazy));
    assign_segtree<add_info>assigned(4,1);assigned.assign(1,3,5);dbg(assigned);
    dual_segtree<add_info>dual(4,vector<ll>{1,2,3,4});dual.apply(1,4,10);dbg(dual);
    dynamic_segtree<add_info,int,true>dynamic(8);auto dynamic_root=dynamic.build();
    dynamic_root=dynamic.set(dynamic_root,3,9);dbg(dynamic,debug::version(dynamic,dynamic_root));
    segtree_2d<add_info>two_dimensional(3,4);two_dimensional.set(1,2,7);dbg(two_dimensional);
    binary_indexed_tree<ll>fenwick(vector<ll>{1,2,3});dbg(fenwick);
    disjoint_set_union uf(5);uf.merge(0,2);uf.merge(1,3);dbg(uf);
    wm_base<unsigned,3>wm;wm.build({3,1,4,1});dbg(wm);
    static_graph<0,int>g(4);g.add_edge(0,1,7);g.add_edge(1,2,8);g.add_edge(1,3,9);dbg(g);
    ::tree<int>tr(4);tr.add_edge(0,1,7);tr.add_edge(1,2,8);tr.add_edge(1,3,9);dbg(tr);
    lowlink ll(g);dbg(ll);dbg(debug::bcc(ll));
    flow<int>network(3);network.add_edge(0,1,4);network.add_edge(1,2,3);dbg(network);
    persistent_array<int,2>pa;auto root=pa.build(4,0);root=pa.change(2,9,root);dbg(pa,debug::version(pa,root));
    ostringstream captured;
    auto output=cout.rdbuf(captured.rdbuf());
    {int dbging=0;dbg(string("hidden"));}
    dbg(123);
    cout.rdbuf(output);
    assert(captured.str().find("hidden")==string::npos);
    assert(captured.str().find("123")!=string::npos);
}
