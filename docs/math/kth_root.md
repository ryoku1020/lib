---
title: kth_root
documentation_of: ../../math/kth_root.hpp
---

# kth_root

整数 `a` に対して `floor(a^(1/b))` を返します。
つまり `x^b<=a` を満たす最大の整数 `x` を求めます。

## 使い方

```cpp
#include "math/kth_root.hpp"

auto x=kth_root(1000,3); // 10
auto y=kth_root(15,2);   // 3
```

## メソッド

- `ull kth_root(ull a,ull b)`
  `floor(a^(1/b))` を返します。

## 計算量

- `O(log a log b)` 程度

## 注意

- `a==0` のときは `0`
- `b==1` のときは `a`
- `b>=64` のときは `1` を返します
- オーバーフローしないように内部で `x^b<=a` を判定しています
