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
- `vc<array<ll,3>> segment_floor(ll N,ll m)`
  `i in [1,m]` を `floor(N/i)` が一定の半開区間へ分割し、各区間を `{l,r,q}`（`floor(N/i)==q` for `l<=i<r`）で返します。

## 計算量

- `floors(n)`: 時間・返り値メモリともに `O(sqrt(n))`
- `segment_floor(N,m)`: 時間・返り値メモリともに `O(sqrt(N))`

## 境界・注意

- `floors` は `n >= 0` を要求します（`assert` あり）。`n==0` のときは空配列を返します。
- `segment_floor` は `0 <= N <= m` で使ってください。`N==0` なら `{{1,m+1,0}}` を返します。
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

for(auto [l,r,q]:segment_floor(n,n)){
    // 全ての i in [l,r) で floor(n/i)==q
}
```
