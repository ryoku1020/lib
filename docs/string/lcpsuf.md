---
title: Suffix Array and LCP Array
documentation_of: ../../string/lcpsuf.hpp
---

# Suffix Array and LCP Array

SA-IS によって suffix array を、Kasai 法によって LCP array を構築します。
文字列だけでなく整数列にも使えます。

## `sf_array`

### `vc<int> sf_array(string s)`
### `vc<int> sf_array(vc<int> s)`

接尾辞配列を返します。
`sa[i]` は辞書順で `i` 番目に小さい suffix の開始位置です。

- 計算量: `O(|s|)`

## `lcp_array`

### `vc<int> lcp_array(string s)`
### `vc<int> lcp_array(vc<int> s)`

LCP 配列を返します。
`lcp[i]` は `sa[i]` と `sa[i+1]` の最長共通接頭辞長です。

- 戻り値の長さは `|s|-1`
- 計算量: `O(|s|)`

## 使用例 1: suffix array を作る

```cpp
#include "string/lcpsuf.hpp"

string s="abracadabra";
auto sa=sf_array(s);
```

## 使用例 2: 異なる部分文字列数

```cpp
string s;
cin>>s;

auto lcp=lcp_array(s);
long long ans=1LL*s.size()*(s.size()+1)/2;
for(int x:lcp)ans-=x;
cout<<ans<<"\n";
```

## 使用例 3: 整数列に使う

```cpp
vector<int> a={3,1,4,1,5,9};
auto sa=sf_array(a);
auto lcp=lcp_array(a);
```

## 注意

- `sf_array` の戻り値には空 suffix は含みません。
- `lcp_array` は内部で `sf_array` を構築してから計算します。
