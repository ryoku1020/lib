---
title: BostanMori
documentation_of: ../../math/bostan_mori.hpp
---

# BostanMori

有理型母関数 `P(x) / Q(x)` の `x^n` 係数を高速に求めます。

## 関数

### `mint BostanMori(FormalPowerSeries<mint> p, FormalPowerSeries<mint> q, long long n)`

`P(x)/Q(x)` の `x^n` 係数を返します。

- 計算量: `O(d log d log n)` 程度

ここで `d` は `Q` の次数です。

## 使用例

```cpp
#include "math/bostan_mori.hpp"

using mint=StaticModInt<998244353>;
using FPS=FormalPowerSeries<mint>;

FPS p={0,1};    // x
FPS q={1,-1,-1}; // 1-x-x^2

mint fn=BostanMori(p,q,n);
```

## 注意

- `fps.hpp` と NTT 環境に依存します。
- `p` と `q` が空なら `0` を返します。
