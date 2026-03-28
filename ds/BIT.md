---
title: BIT (Binary Indexed Tree / Fenwick Tree)
documentation_of: ./BIT.hpp
---

# BIT (Binary Indexed Tree / Fenwick Tree)

長さ $N$ の配列 $a_0, a_1, \dots, a_{N-1}$ に対して、一点加算と区間和の取得を $O(\log N)$ で行うデータ構造です。
内部的には 1-indexed で管理していますが、ユーザーインターフェースは 0-indexed になっています。区間は半開区間 $[l, r)$ で指定します。

## 使い方

```cpp
#include "ds/BIT.cpp"

// 長さ N で初期化。初期値はすべて 0
BIT<long long> bit(N);

// 配列から初期化。O(N)
vector<long long> a = {1, 2, 3, 4, 5};
BIT<long long> bit(a);

// i 番目の要素に x を加算。a[i] += x と同じ。
bit.add(i, x);

// 区間 [l, r) の和を求める。
long long sum = bit.sum(l, r);
```

## メソッド

### `BIT()`
空の BIT を構築します。
- 計算量: $O(1)$

### `BIT(int N)`
長さ $N$ の BIT を構築します。各要素は 0 で初期化されます。
- 計算量: $O(N)$

### `BIT(const std::vector<T>& a)`
配列 `a` の要素で BIT を構築します。
- 計算量: $O(N)$ (ただし $N$ は配列 `a` の長さ)

### `void add(int i, T x)`
$i$ 番目 (0-indexed) の要素に $x$ を加算します。すなわち $a_i \leftarrow a_i + x$ とします。
- 制約: $0 \le i < n$
- 計算量: $O(\log N)$

### `T sum(int l, int r)`
半開区間 $[l, r)$ の要素の和、すなわち $\sum_{i=l}^{r-1} a_i$ を返します。
- 制約: $0 \le l \le r \le n$
- 計算量: $O(\log N)$

### `int lower_bound(T w)`
$a_i \ge 0$ であることを前提とし、$a_0 + a_1 + \dots + a_x \ge w$ となる最小の $x$ を返します。そのような $x$ が存在しない場合は $N$ を返します ($w \le 0$ のときは 0 を返します)。
- 制約: 全ての要素 $a_i \ge 0$
- 計算量: $O(\log N)$
