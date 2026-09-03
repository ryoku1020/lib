---
title: static_range_mode
documentation_of: ../../ds/sequence/static-mode.hpp
---

# static_range_mode

静的配列に対する区間最頻値クエリです。
一度前計算したあと、各区間 `[l,r)` の mode とその出現回数を返します。

## 使い方

```cpp
#include "ds/sequence/static-mode.hpp"

static_range_mode<int> rmq(7);
vector<int> a={1,2,1,3,1,2,2};
for(int i=0;i<7;i++)rmq.set(i,a[i]);
rmq.precalc();

auto [cnt,val]=rmq.query(0,7);
// val は最頻値, cnt はその出現回数
```

## メソッド

- `static_range_mode(int n)`
  長さ `n` で初期化します。

  - 制約: `n>=0`
  - 計算量: `O(n)`

- `void set(int i,T x)`
  `a[i]=x` を設定します。

  - 制約: `precalc()` 前、`0<=i<n`
  - 計算量: `O(1)`

- `void precalc()`
  前計算を行います。`query` の前に必須です。

  - 制約: `n>0`
  - 計算量: `O(n sqrt(n)+n log n)`

- `pair<int,T> query(int l,int r)`
  区間 `[l,r)` の最頻値を `{出現回数,値}` で返します。

  - 制約: `0<=l<r<=n`
  - 計算量: `O(sqrt(n))`

## 計算量

前計算は `O(n sqrt(n)+n log n)`、クエリは 1 回 `O(sqrt(n))`、使用メモリは `O(n)` です。最初の `query` は内部で `precalc()` を呼ぶため、前計算時間も含みます。

## 境界・注意

- `l<r` が必要です。空区間は扱えません。
- `n==0` では `precalc()` が `assert` で停止するため、空配列はクエリできません。
- 値は内部で座標圧縮されます。
- 複数の最頻値がある場合、実装の比較順に従って 1 つ返ります。

## 使用例: majority 判定

```cpp
auto [cnt,val]=rmq.query(l,r);
if(cnt>(r-l)/2){
    // val は majority
}
```
