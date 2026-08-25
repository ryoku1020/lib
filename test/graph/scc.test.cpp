#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../graph/connectivity/scc.hpp"
#include "../../graph/base.hpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    static_graph<1, int> g(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        g.add_edge(u, v);
    }

    auto comp_id = scc(g);

    int k = 0;
    for (int id : comp_id) k = max(k, id + 1);

    vector<vector<int>> comps(k);
    for (int i = 0; i < N; i++) {
        comps[comp_id[i]].push_back(i);
    }

    cout << k << "\n";
    for (int i = 0; i < k; i++) {
        cout << comps[i].size();
        for (int v : comps[i]) {
            cout << " " << v;
        }
        cout << "\n";
    }
    return 0;
}
