---
title: Suffix Array & LCP Array (接尾辞配列と最長共通接頭辞)
documentation_of: ../../string/lcpsuf.hpp
---

# Suffix Array & LCP Array (接尾辞配列と最長共通接頭辞)

SA-IS法を用いて、文字列 (または配列) のすべての接尾辞を辞書順にソートした配列 (Suffix Array) を $O(N)$ で構築します。
また、Kasai's Algorithm により、隣り合う接尾辞の最長共通接頭辞 (LCP Array) を $O(N)$ で計算します。

## 使い方

```cpp
#include "string/lcpsuf.cpp"

string s = "abracadabra";

// Suffix Array の構築
// sf[i] = 辞書順で i 番目に小さい接尾辞の開始インデックス
vector<int> sf = sf_array(s);

// LCP Array の構築
// lcp[i] = sf[i] 番目の接尾辞と sf[i+1] 番目の接尾辞の LCP 長
vector<int> lcp = lcp_array(s);
```

## メソッド

### `vector<int> sf_array(string s)`
### `vector<int> sf_array(vector<int> s)`
文字列 `s` (または整数配列 `s`) の接尾辞配列 (Suffix Array) を構築して返します。
SA-IS (Suffix Array Induced Sorting) 法を用いており、高速に動作します。
戻り値の配列の長さは $|s|$ です (空文字列の接尾辞は含まれません)。
- 計算量: $O(|s|)$

### `vector<int> lcp_array(string s)`
### `vector<int> lcp_array(vector<int> s)`
文字列 `s` (または整数配列 `s`) に対して、隣接する接尾辞間の最長共通接頭辞の長さ (LCP Array) を計算して返します。
内部的に `sf_array` を呼び出したのち、Kasai's Algorithm で計算します。
戻り値 `lcp` の長さは $|s| - 1$ となります。`lcp[i]` には、Suffix Array 上で $i$ 番目と $i+1$ 番目の接尾辞の最長共通接頭辞の長さが格納されます。
- 計算量: $O(|s|)$
