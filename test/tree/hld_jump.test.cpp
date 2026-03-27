#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "../../tree/HLD.cpp"
#include <iostream>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    HLD hld(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.ae(u, v);
    }
    hld.build();

    for (int i = 0; i < Q; i++) {
        int s, t, k;
        cin >> s >> t >> k;
        cout << hld.jump(s, t, k) << "\n";
    }
    return 0;
}
