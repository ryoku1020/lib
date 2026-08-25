#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include <iostream>
#include <vector>
#include "../../ds/segment_tree/segtree.hpp"
#include "../../math/modular/static-mod-int.hpp"

using namespace std;

using mint = static_modint<998244353>;

struct info {
    using value_type = pair<mint, mint>; // a, b for ax+b
    static value_type op(value_type a, value_type b) {
        // b(a(x)) = b.a * a.a * x + b.a * a.b + b.b
        return {b.first * a.first, b.first * a.second + b.second};
    }
    static value_type e() {
        return {1, 0};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    segtree<info> seg(N);
    for (int i = 0; i < N; i++) {
        long long a, b;
        cin >> a >> b;
        seg.set(i, {a, b});
    }

    for (int i = 0; i < Q; i++) {
        int type;
        cin >> type;
        if (type == 0) {
            int p;
            long long c, d;
            cin >> p >> c >> d;
            seg.set(p, {c, d});
        } else {
            int l, r;
            long long x;
            cin >> l >> r >> x;
            auto f = seg.prod(l, r);
            cout << (f.first * x + f.second).val << "\n";
        }
    }
    return 0;
}
