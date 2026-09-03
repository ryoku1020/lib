---
title: Binary Indexed tree
documentation_of: ../../ds/sequence/BIT.hpp
---

# Binary Indexed tree

Fenwick tree です。
長さ `N` の列に対して、1 点加算と区間和取得を `O(log N)` で行えます。

## コンストラクタ

### `binary_indexed_tree()`

空の bit を作ります。

- 計算量: `O(1)`

### `binary_indexed_tree(int N)`

長さ `N`、初期値 0 の列を作ります。

- 制約: `0<=N`
- 計算量: `O(N)`

### `binary_indexed_tree(const vector<T>& a)`

配列 `a` で初期化します。

- 計算量: `O(N)`

## メソッド

### `void bit.add(int p, T x)`

`a[p]+=x` とします。

- 制約: `0<=p<n`
- 計算量: `O(log n)`

### `T bit.sum(int l, int r)`

`a[l]+...+a[r-1]` を返します。

- 制約: `0<=l<=r<=n`
- 計算量: `O(log n)`

### `int bit.lower_bound(T w)`

`a[i]>=0` を仮定し、
`a[0]+a[1]+...+a[x-1] < w <= a[0]+...+a[x]`
となる最小の `x` を返します。

言い換えると、prefix sum が初めて `w` 以上になる位置です。

- `w<=0` なら `0`
- 存在しないなら `n`

- 制約: 各 `a[i]>=0`
- 計算量: `O(log n)`

## 境界・注意

- インターフェースは 0-indexed、内部実装は 1-indexed です。
- 区間は半開区間 `[l,r)` です。

## 使用例

```cpp
#include "ds/sequence/BIT.hpp"

binary_indexed_tree<long long> bit(N);

bit.add(3,5);
bit.add(7,2);

auto s=bit.sum(0,8);
auto t=bit.sum(l,r);
```

## 使用例: k 番目の 1 を探す

`0/1` 配列を持っていて、「左から `k` 番目の 1 の位置」を探したいときに `lower_bound` が使えます。

```cpp
int k=5; // 1-indexed
int pos=bit.lower_bound(k);
```
