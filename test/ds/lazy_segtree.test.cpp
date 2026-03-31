#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <iostream>
#include <vector>
#include "../../ds/lazy_seg.hpp"
#include "../../math/s_mint.hpp"

using namespace std;

using mint = StaticModInt<998244353>;

struct Info {
    using value_type = pair<mint, mint>; // sum, len
    static value_type op(value_type a, value_type b) {
        return {a.first + b.first, a.second + b.second};
    }
    static value_type e() {
        return {0, 0};
    }
    static value_type leaf() {
        return {0, 1};
    }
};

struct Tag {
    using lazy_type = pair<mint, mint>; // a, b
    static lazy_type Merge(lazy_type parent, lazy_type child) {
        return {child.first * parent.first, child.first * parent.second + child.second};
    }
    static lazy_type id() {
        return {1, 0};
    }
    static Info::value_type Apply(Info::value_type node, lazy_type lazy_type) {
        return {node.first * lazy_type.first + node.second * lazy_type.second, node.second};
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

    LazySegmentTree<Info, Tag> seg(N, A);

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
