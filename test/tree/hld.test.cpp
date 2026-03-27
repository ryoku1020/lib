#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "../../tree/HLD.cpp"
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    HLD hld(N);
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        hld.ae(i, p);
    }
    hld.build();

    for (int i = 0; i < Q; i++) {
        int u, v;
        cin >> u >> v;
        cout << hld.lca(u, v) << "\n";
    }
    return 0;
}
