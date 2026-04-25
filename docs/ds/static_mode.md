---
title: StaticRangeMode
documentation_of: ../../ds/static_mode.hpp
---

# StaticRangeMode

静的配列に対する区間最頻値クエリです。
一度前計算したあと、各区間 `[l,r)` の mode とその出現回数を返します。

## 使い方

```cpp
#include "ds/static_mode.hpp"

StaticRangeMode<int> rmq(7);
vector<int> a={1,2,1,3,1,2,2};
for(int i=0;i<7;i++)rmq.set(i,a[i]);
rmq.precalc();

auto [cnt,val]=rmq.Query(0,7);
// val は最頻値, cnt はその出現回数
```

## メソッド

- `StaticRangeMode(int n)`
  長さ `n` で初期化します。

- `void set(int i,T x)`
  `a[i]=x` を設定します。

- `void precalc()`
  前計算を行います。`Query` の前に必須です。

- `pair<int,T> Query(int l,int r)`
  区間 `[l,r)` の最頻値を `{出現回数,値}` で返します。

## 典型例

```cpp
auto [cnt,val]=rmq.Query(l,r);
if(cnt>(r-l)/2){
    // val は majority
}
```

## 注意

- `l<r` が必要です。空区間は扱えません。
- 値は内部で座標圧縮されます。
- 複数の最頻値がある場合、実装の比較順に従って 1 つ返ります。
