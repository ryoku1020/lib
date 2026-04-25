---
title: prime_counting
documentation_of: ../../math/prime_counting.hpp
---

# prime_counting

`pi(n)`、つまり `n` 以下の素数の個数を求めます。
`floor(n/k)` の distinct な値をまとめて扱うことで、高速に素数個数を数えています。

## 使い方

```cpp
#include "math/prime_counting.hpp"

cout<<prime_counting(10)<<"\n";   // 4
cout<<prime_counting(100)<<"\n";  // 25
```

## メソッド

- `ll prime_counting(ll n)`
  `n` 以下の素数の個数を返します。

## 計算量

- おおよそ `O(n^{3/4}/log n)` 系の実用的な高速素数計数です。

## 注意

- `n` は `ll` で渡します。
- 内部で [docs/math/enumerate_floor.md](/Users/ryoku_/Desktop/cp/lib/docs/math/enumerate_floor.md) の `floors` を使っています。
