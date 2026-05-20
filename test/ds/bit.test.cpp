#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <iostream>
#include "../../ds/bit.hpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<long long> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }
    BIT<long long> tbit(a);

    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int p;
            long long x;
            cin >> p >> x;
            tbit.add(p, x);
        } else {
            int l, r;
            cin >> l >> r;
            cout << tbit.sum(l, r) << "\n";
        }
    }
    return 0;
}
