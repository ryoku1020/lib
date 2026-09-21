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
    unprintable x{7};
    printable_info custom{3,5};
    assert(debug::to_string(x).find("<unprintable unprintable>")!=string::npos);
    assert(debug::to_string(vector<unprintable>{{1},{2}}).find("<unprintable unprintable>")!=string::npos);
    assert(debug::to_string(custom)=="{sum=3, mx=5}");
    assert(debug::to_string(bitset<8>(0b01001101))=="index : 01234567\nbit   : 10110010");
    assert(debug::to_string('\n')=="'\\n'");
    char chars[3]={'a','\0','b'};
    assert(debug::to_string(chars)=="\"a\\0b\"");
    vector<int>large(1000);iota(large.begin(),large.end(),0);
    auto shortened=debug::to_string(large);
    assert(shortened.find("0, 1, 2")!=string::npos&&shortened.find("997, 998, 999")!=string::npos);
    assert(shortened.find("more")==string::npos&&shortened.find("…")!=string::npos);
    assert(debug::to_string(debug::full(large)).find("…")==string::npos);
    assert(debug::to_string(set<int>{1,3,8,12})=="{1, 3, 8, 12}");
    assert(debug::to_string(map<int,int>{{1,10},{3,27},{8,-1}})=="{1: 10, 3: 27, 8: -1}");
    string long_string(300,'x');
    assert(debug::to_string(long_string).find("…")!=string::npos);
    assert(debug::to_string(debug::full(long_string)).find("…")==string::npos);
    vector<vector<int>>matrix{{0,inf<int>,8,11},{-1,2,4,7},{0,100,20,3}};
    assert(debug::to_string(matrix).find("∞")!=string::npos);
    vector<vector<int>>ragged{{1,2},{3}};
    assert(debug::to_string(ragged)=="[[1, 2], [3]]");
    vector<vector<int>>large_matrix(20,vector<int>(20));
    for(int y=0;y<20;y++)for(int z=0;z<20;z++)large_matrix[y][z]=y*100+z;
    auto matrix_rows=debug::config.max_matrix_rows,matrix_columns=debug::config.max_matrix_columns;
    debug::config.max_matrix_rows=4;debug::config.max_matrix_columns=4;
    auto shortened_matrix=debug::to_string(large_matrix);
    debug::config.max_matrix_rows=matrix_rows;debug::config.max_matrix_columns=matrix_columns;
    assert(shortened_matrix.find(" 0 |")!=string::npos&&shortened_matrix.find("19 |")!=string::npos);
    assert(shortened_matrix.find(" 19")!=string::npos&&shortened_matrix.find("⋮")!=string::npos);
    int i=12,l=3,r=18;
    dbg(i);dbg(i,l,r);
    dbg(1,"abc",string("abc"),vector<int>{1,2,3},matrix);
    dbg(large);
    dbg(make_pair(1,2),tuple<int,string>{3,"x"},optional<int>{4},variant<int,string>{"v"});
    bitset<8>bits(0b01001101);dbg(bits);
    bitset<130>long_bits;long_bits.set(0);long_bits.set(64);long_bits.set(129);dbg(long_bits);
    bitset<1000>huge_bits;
    assert(debug::to_string(huge_bits).find("…")!=string::npos);
    assert(debug::to_string(debug::full(huge_bits)).find("…")==string::npos);
    dbg(x,vector<unprintable>{{1},{2}});
    dbg(custom);
    segtree<sum_info>seg(3,[&](int i){return unprintable{i+1};});
    dbg(seg);dbg(debug::tree(seg));
    segtree<add_info>small_seg(vector<ll>{1,1});
    auto tree_nodes=debug::config.max_tree_nodes;
    debug::config.max_tree_nodes=3;assert(debug::to_string(debug::tree(small_seg)).find("…")==string::npos);
    debug::config.max_tree_nodes=2;assert(debug::to_string(debug::tree(small_seg)).find("…")!=string::npos);
    debug::config.max_tree_nodes=tree_nodes;
    lazy_segtree<add_info,add_tag>lazy(4,vector<ll>{1,2,3,4});
    lazy.apply(1,4,10);dbg(lazy);dbg(debug::tree(lazy));dbg(debug::raw(lazy));
    assign_segtree<add_info>assigned(4,1);assigned.assign(1,3,5);dbg(assigned);
    dual_segtree<add_info>dual(4,vector<ll>{1,2,3,4});dual.apply(1,4,10);dbg(dual);
    dynamic_segtree<add_info,int,true>dynamic(8);auto dynamic_root=dynamic.build();
    dynamic_root=dynamic.set(dynamic_root,3,9);dbg(dynamic,debug::version(dynamic,dynamic_root));
    segtree_2d<add_info>two_dimensional(3,4);two_dimensional.set(1,2,7);dbg(two_dimensional);
    binary_indexed_tree<ll>fenwick(vector<ll>{1,2,3});dbg(fenwick);
    disjoint_set_union uf(5);uf.merge(0,2);uf.merge(1,3);dbg(uf);
    wm_base<unsigned,3>wm;wm.build({3,1,4,1});dbg(wm);
    static_graph<0,int>g(4);g.add_edge(0,1,7);g.add_edge(1,2,8);g.add_edge(1,3,9);dbg(g);
    static_graph<1,unweighted>large_graph(100);
    auto graph_vertices=debug::config.max_graph_vertices;debug::config.max_graph_vertices=4;
    auto shortened_graph=debug::to_string(large_graph);debug::config.max_graph_vertices=graph_vertices;
    assert(shortened_graph.find("0 ->")!=string::npos&&shortened_graph.find("99 ->")!=string::npos);
    assert(shortened_graph.find("…")!=string::npos);
    ::tree<int>tr(4);tr.add_edge(0,1,7);tr.add_edge(1,2,8);tr.add_edge(1,3,9);dbg(tr);
    lowlink ll(g);dbg(ll);dbg(debug::bcc(ll));
    flow<int>network(3);network.add_edge(0,1,4);network.add_edge(1,2,3);dbg(network);
    persistent_array<int,2>pa;auto root=pa.build(4,0);root=pa.change(2,9,root);dbg(pa,debug::version(pa,root));
    ostringstream captured,errors;
    auto output=cout.rdbuf(captured.rdbuf());
    auto error=cerr.rdbuf(errors.rdbuf());
    {int dbging=0;dbg(string("hidden"));}
    dbg(123);
    debug::internal::log(__FILE__,__LINE__,__func__,"broken(",1,2);
    cout<<"ordinary-output\n";
    cout.rdbuf(output);
    cerr.rdbuf(error);
    assert(captured.str().find("hidden")==string::npos);
    assert(captured.str().find("123")!=string::npos);
    assert(captured.str().find("arg0 = 1")!=string::npos);
    assert(captured.str().find("arg1 = 2")!=string::npos);
    assert(captured.str().find("ordinary-output")!=string::npos);
    assert(captured.str().find("\033[")==string::npos);
    assert(errors.str().empty());
}
