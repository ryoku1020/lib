#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
#include"../../ds/segment_tree/lazy-segtree.hpp"
#include"../../ds/act/mul-affine.hpp"
#include"../../math/modular/static-mod-int.hpp"
using namespace ryoku;
using mint=static_modint<998244353>;
int main(){
    INT(N,Q);
    vc<mint>A(N);
    rep(i,N){
        LL(x);
        A[i]=x;
    }
    lazy_segtree<affine_sum<mint>>seg(N,A);
    rep(i,Q){
        INT(type,l,r);
        if(type==0){
            LL(b,c);
            seg.apply(l,r,{b,c});
        }else{
            cout<<seg.prod(l,r).val<<"\n";
        }
    }
    return 0;
}
