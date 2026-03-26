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
        // applying child then parent => a_p(a_c x + b_c) + b_p
        // = (a_p * a_c) x + a_p * b_c + b_p
        // But Tag::Merge signature in lazy_seg.cpp:
        // `lazy[k] = Tag::Merge(lazy[k], x);`
        // where x is the new tag.
        // Wait, if lazy[k] was applied before, and x is the NEW tag,
        // then the function applied is x(lazy[k](v)).
        // So a_new(a_old x + b_old) + b_new = a_new a_old x + a_new b_old + b_new.
        // Wait, let's trace `all_apply(k, x)`: `node[k] = Tag::Apply(node[k], x); lazy[k] = Tag::Merge(lazy[k], x);`
        // x is the *newer* operation. So we apply x after lazy[k].
        // (a_x, b_x) o (a_l, b_l) = a_x(a_l * v + b_l) + b_x = a_x a_l * v + a_x b_l + b_x
        // Thus first is child.first * parent.first, second is child.first * parent.second + child.second
        // Here parent = lazy[k], child = x.
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
