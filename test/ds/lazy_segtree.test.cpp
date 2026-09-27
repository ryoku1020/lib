#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

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
