---
title: BostanMori
documentation_of: ../../math/bostan-mori.hpp
---

# BostanMori

有理型母関数 `P(x) / Q(x)` の `x^n` 係数を高速に求めます。

## 関数

### `mint BostanMori(FormalPowerSeries<mint> p, FormalPowerSeries<mint> q, long long n)`

`P(x)/Q(x)` の `x^n` 係数を返します。

- 計算量: `O(d log d log n)` 程度

ここで `d` は `Q` の次数です。

## 境界・注意

- `fps.hpp` と NTT 環境に依存します。
- `q[0] != 0` が必要です（アサートあり）。
- `n >= 0` が必要です（アサートあり）。
- `p` と `q` が空なら `0` を返します。
- `P` と `Q` は `gcd(P, Q) = 1` でなくても動作しますが、`P` の次数は `Q` の次数未満であることが推奨されます（それ以外は未定義動作になる可能性あり）。

## 使用例

```cpp
#include "math/bostan-mori.hpp"

using mint=StaticModInt<998244353>;
using FPS=FormalPowerSeries<mint>;

FPS p={0,1};    // x
FPS q={1,-1,-1}; // 1-x-x^2

mint fn=BostanMori(p,q,n);
```

