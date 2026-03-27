#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <iostream>
#include <vector>
#include <algorithm>
#include "../../graph/scc.hpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    StronglyConnectedComponents sc(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        sc.add(u, v);
    }

    auto res = sc.do_scc();

    cout << res.size() << "\n";
    for (int i = 0; i < (int)res.size(); i++) {
        cout << res[i].size();
        for (int v : res[i]) {
            cout << " " << v;
        }
        cout << "\n";
    }
    return 0;
}
