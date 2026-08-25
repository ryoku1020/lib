#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"

#include "../../string/suffix-array.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string S;
    cin >> S;

    auto sa = suffix_array(S);
    for (int i = 0; i < sa.size(); i++) {
        cout << sa[i] << (i == sa.size() - 1 ? "" : " ");
    }
    cout << "\n";
    return 0;
}
