#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../ds/sparse_table.hpp"

using namespace std;

struct Info {
    using value_type = long long;
    static value_type op(value_type a, value_type b) {
        return min(a, b);
    }
    static value_type e() {
        return 1e18;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    SparseTable<Info> st(N);
    for (int i = 0; i < N; i++) {
        long long a;
        cin >> a;
        st.set(i, a);
    }
    st.build();

    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        cout << st.prod(l, r) << "\n";
    }
    return 0;
}
