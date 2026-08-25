---
title: Suffix Array and LCP Array
documentation_of: ../../string/suffix-array.hpp
---

# Suffix Array and LCP Array

SA-IS で suffix array を、Kasai 法で LCP array を構築します。
文字列だけでなく整数列にも使えます。

## 関数

### `vector<int> suffix_array(string s)`
### `vector<int> suffix_array(vector<int> s)`

接尾辞配列を返します。

- `sa[i]` — 辞書順で `i` 番目の suffix の開始位置（0-indexed）
- 返り値の長さは `|s|`
- `sa[0]` は辞書順最小の suffix の開始位置
- 整数列版: 値は任意の整数でよい（内部で座標圧縮）
- 計算量: `O(|s|)`

### `vector<int> lcp_array(string s, vector<int> sa)`
### `vector<int> lcp_array(vector<int> s, vector<int> sa)`

LCP 配列を返します。suffix array `sa` を引数に取ります。

- `lcp[i]` — `sa[i]` から始まる suffix と `sa[i+1]` から始まる suffix の最長共通接頭辞の長さ
- 返り値の長さは `|s| - 1`（空文字列に対しては空配列）
- 計算量: `O(|s|)`

## 境界・注意

- `suffix_array` の返り値には空 suffix（位置 `|s|`）は含まれません。
- `lcp_array` は `suffix_array` の結果を受け取って構築します。
- 整数列版の `suffix_array` は内部で値を座標圧縮します。

## 使用例 1: 接尾辞配列の構築

```cpp
#include "string/suffix-array.hpp"

string s = "abracadabra";
auto sa = suffix_array(s);
// sa = {10,7,0,3,5,8,1,4,6,9,2} など
```

## 使用例 2: 異なる部分文字列の個数

```cpp
string s;
cin >> s;
int n = s.size();
auto sa  = suffix_array(s);
auto lcp = lcp_array(s, sa);

// 全部分文字列数 - 重複 = n*(n+1)/2 - sum(lcp)
long long ans = (long long)n*(n+1)/2;
for (int x : lcp) ans -= x;
cout << ans << "\n";
```

## 使用例 3: 整数列

```cpp
vc<int> a = {3, 1, 4, 1, 5, 9};
auto sa  = suffix_array(a);
auto lcp = lcp_array(a, sa);
```

## 使用例 4: 2 つの文字列を繋いで LCP クエリ

`s + "#" + t` にして suffix array を作り、`sa` と `lcp` から sparse table を引くパターンです。

```cpp
string s, t;
// s と t を区切り文字で連結
string st = s + "#" + t; // '#' は s, t に含まれない文字
auto sa = suffix_array(st);
auto lcp = lcp_array(st, sa);
// lcp の上で sparse table を作り RMQ で LCP クエリ
```
