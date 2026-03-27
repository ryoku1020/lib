#define PROBLEM "https://judge.yosupo.jp/problem/number_of_substrings"

#include "../../string/lcpsuf.cpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    auto lcp = lcp_array(S);
    long long ans = 1LL * S.size() * (S.size() + 1) / 2;
    for (int x : lcp) ans -= x;
    cout << ans << "\n";
    return 0;
}
