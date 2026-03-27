#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"
#include <iostream>
#include <vector>
#include "../../graph/bipartite_match.hpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, R, M;
    if (!(cin >> L >> R >> M)) return 0;

    BipartiteMatching bm(L, R);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        bm.add_edge(u, v);
    }

    auto ans = bm.work();
    cout << ans.size() << "\n";
    for (auto p : ans) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}
