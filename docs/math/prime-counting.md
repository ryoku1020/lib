---
title: prime-counting
documentation_of: ../../math/number_theory/prime-counting.hpp
---

# prime-counting

`pi(n)`、つまり `n` 以下の素数の個数を求めます。
`floor(n/k)` の distinct な値をまとめて扱うことで、高速に素数個数を数えています。

## 使い方

```cpp
#include "math/number_theory/prime-counting.hpp"

cout<<prime_counting(10)<<"\n";   // 4
cout<<prime_counting(100)<<"\n";  // 25
```

## メソッド

- `ll prime_counting(ll n)`
  `n` 以下の素数の個数を返します。

## 計算量

- おおよそ `O(n^{3/4}/log n)` 系の実用的な高速素数計数です。

## 境界・注意

- `n` は `ll` で渡します。
- 内部で [docs/math/enumerate-floor.md](/Users/ryoku_/Desktop/cp/lib/docs/math/enumerate-floor.md) の `floors` を使っています。

## 使用例

区間 `(L,R]` に含まれる素数の個数を求めます。

```cpp
long long L,R;
cin>>L>>R;

long long ans=prime_counting(R)-prime_counting(L);
cout<<ans<<"\n";
```
