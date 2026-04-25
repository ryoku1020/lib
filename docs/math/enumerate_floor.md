---
title: enumerate_floor
documentation_of: ../../math/enumerate_floor.hpp
---

# enumerate_floor

`floor(n/k)` が取りうる値をまとめて扱うときに使う補助関数です。
`1...n` の全部を舐める代わりに、異なる値だけを列挙したい場面で便利です。

## 使い方

```cpp
#include "math/enumerate_floor.hpp"

auto xs=floors(10);
// {1,2,3,5,10}
```

`10/1=10, 10/2=5, 10/3=3, 10/4=2, ...` のように、
`floor(10/k)` が取りうる異なる値を昇順に並べたものになっています。

## メソッド

- `vc<ll> floors(ll n)`
  `floor(n/k)` が取りうる値全体を昇順で返します。

## 計算量

- `O(sqrt(n))`

## 注意

- `n==0` のときは空配列を返します。
- `prime_counting` のような `n/x` をまとめて扱う実装でよく使います。
