---
title: enumerate-floor
documentation_of: ../../math/number_theory/enumerate-floor.hpp
---

# enumerate-floor

`floor(n/k)` が取りうる値をまとめて扱うときに使う補助関数です。
`1...n` の全部を舐める代わりに、異なる値だけを列挙したい場面で便利です。

## 使い方

```cpp
#include "math/number_theory/enumerate-floor.hpp"

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

## 境界・注意

- `n==0` のときは空配列を返します。
- `prime_counting` のような `n/x` をまとめて扱う実装でよく使います。

## 使用例

`floor(n/i)` が同じ値になる区間をまとめて処理します。

```cpp
long long n;
cin>>n;

auto vals=floors(n);
for(long long q:vals){
    long long l=n/(q+1)+1;
    long long r=n/q;
    // i in [l,r] では floor(n/i)==q
}
```
