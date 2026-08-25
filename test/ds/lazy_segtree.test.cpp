#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <iostream>
#include <vector>
#include "../../ds/segment_tree/lazy-segtree.hpp"
#include "../../math/modular/static-mod-int.hpp"

using namespace std;

using mint = static_modint<998244353>;

struct info {
    using value_type = pair<mint, mint>;

    static value_type op(value_type a, value_type b) {
        return {a.first + b.first, a.second + b.second};
    }
    static value_type e() {
        return {0, 0};
    }
};

struct tag {
    using lazy_type = pair<mint, mint>;

    static lazy_type merge(lazy_type parent, lazy_type child) {
        return {child.first * parent.first, child.first * parent.second + child.second};
    }
    static lazy_type id() {
        return {1, 0};
    }
    static info::value_type apply(info::value_type node, lazy_type lz) {
        return {node.first * lz.first + node.second * lz.second, node.second};
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<pair<mint, mint>> A(N);
    for (int i = 0; i < N; i++) {
        long long x;
        cin >> x;
        A[i] = {x, 1};
    }

    lazy_segtree<info, tag> seg(N, A);

    for (int i = 0; i < Q; i++) {
        int type;
        cin >> type;
        if (type == 0) {
            int l, r;
            long long b, c;
            cin >> l >> r >> b >> c;
            seg.apply(l, r, {b, c});
        } else {
            int l, r;
            cin >> l >> r;
            cout << seg.prod(l, r).first.val << "\n";
        }
    }
    return 0;
}
