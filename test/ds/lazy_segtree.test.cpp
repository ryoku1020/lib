#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include <iostream>
#include <vector>
#include "../../ds/lazy_seg.cpp"
#include "../../math/s_mint.cpp"

using namespace std;

using mint = s_mint<998244353>;

struct Tag {
    using lazy_type = pair<mint, mint>; // a, b
    static lazy_type Merge(lazy_type parent, lazy_type child) {
        return {child.first * parent.first, child.first * parent.second + child.second};
    }
    static lazy_type id() {
        return {1, 0};
    }
    static pair<mint, mint> Apply(pair<mint, mint> node, lazy_type tag) {
        return {node.first * tag.first + node.second * tag.second, node.second};
    }
};

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

    lazy_segtree<Info, Tag> seg(N, A);

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
