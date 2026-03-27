#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../string/lcpsuf.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    auto sa = sf_array(S);
    for (int i = 0; i < sa.size(); i++) {
        cout << sa[i] << (i == sa.size() - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}
