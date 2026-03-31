#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../tree/HLD.hpp"
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    HeavyLightDecomposition hld(N);
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        hld.add_edge(i, p);
    }
    hld.build();

    for (int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;
        cout << hld.lca(u, v) << "\n";
    }
    return 0;
}
