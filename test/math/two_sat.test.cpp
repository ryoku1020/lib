#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include <iostream>
#include <vector>
#include "../../graph/two_sat.hpp"

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string p, cnf;
    int n, m;
    cin >> p >> cnf >> n >> m;

    TwoSatisfiability ts(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        ts.add_clause(abs(u) - 1, u > 0, abs(v) - 1, v > 0);
    }

    if (ts.satisfiable()) {
        cout << "s SATISFIABLE\n";
        cout << "v ";
        auto ans = ts.answer();
        for (int i = 0; i < n; i++) {
            if (ans[i]) cout << i + 1 << " ";
            else cout << -(i + 1) << " ";
        }
        cout << "0\n";
    } else {
        cout << "s UNSATISFIABLE\n";
    }
    return 0;
}
