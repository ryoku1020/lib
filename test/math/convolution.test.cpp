#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <iostream>
#include <vector>
#include "../../math/convolution/conv.hpp"

using namespace std;
using namespace atcoder;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<long long> a(N), b(M);
    for (int i = 0; i < N; i++) cin >> a[i];
    for (int i = 0; i < M; i++) cin >> b[i];

    auto c = convolution<998244353>(a, b);
    for (int i = 0; i < N + M - 1; i++) {
        cout << c[i] << (i == N + M - 2 ? "" : " ");
    }
    cout << "\n";
    return 0;
}
