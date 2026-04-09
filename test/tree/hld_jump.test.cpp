#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "../../tree/base.hpp"
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    static_graph<1> g(N);
    Tree hld(N, g);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }
    hld.build();

    for (int i = 0; i < Q; i++) {
        int s, t, k;
        cin >> s >> t >> k;
        cout << hld.jump(s, t, k) << "\n";
    }
    return 0;
}
