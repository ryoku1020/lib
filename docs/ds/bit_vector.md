---
title: bit_vector
documentation_of: ../../ds/bit_vector.hpp
---

# bit_vector

0/1 列に対する `rank` クエリ専用の軽量 bit vector です。
Wavelet Matrix などの下請けとして使うことを想定した実装です。

## 使い方

```cpp
#include "ds/bit_vector.hpp"

vector<int> bits={1,0,1,1,0,0,1};
bit_vector bv(bits);

int x=bv.rank1(5);    // [0,5) にある 1 の個数
int y=bv.rank0(2,7);  // [2,7) にある 0 の個数
```

## メソッド

- `bit_vector(const vc<int>& v)`
  `0/1` 配列 `v` から構築します。

- `int rank1(int r)`
  半開区間 `[0,r)` に含まれる 1 の個数を返します。

- `int rank1(int l,int r)`
  半開区間 `[l,r)` に含まれる 1 の個数を返します。

- `int rank0(int r)`
  半開区間 `[0,r)` に含まれる 0 の個数を返します。

- `int rank0(int l,int r)`
  半開区間 `[l,r)` に含まれる 0 の個数を返します。

## 計算量

- 構築: `O(n)`
- 各 `rank`: `O(1)`

## 注意

- 入力は `0/1` を想定しています。
- `select` は実装されていません。
