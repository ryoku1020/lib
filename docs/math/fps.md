---
title: FormalPowerSeries
documentation_of: ../../math/fps.hpp
---

# FormalPowerSeries

形式的冪級数です。
NTT を使って積、逆数、対数、指数、冪、平方根などを高速に計算します。

## 型

### `FormalPowerSeries<mint>`

`vector<mint>` を継承した多項式型です。
通常は NTT friendly mod の `StaticModInt` と組み合わせます。

```cpp
using mint=StaticModInt<998244353>;
using FPS=FormalPowerSeries<mint>;
```

## 主な演算

- `+`, `-`, `*`
- 定数との `+`, `-`, `*`, `/`
- `<<`, `>>`
  `x^k` のシフト

## 主なメソッド

### `poly pre(int sz) const`

先頭 `sz` 項だけを取ります。

### `poly inv(int deg = -1) const`

逆数 `1/f` を `x^deg` 未満で返します。
`f[0]!=0` が必要です。

### `poly diff() const`
### `poly integral() const`

微分、積分です。

### `poly log(int deg = -1) const`

`log(f)` を返します。
`f[0]=1` が必要です。

### `poly exp(int deg = -1) const`

`exp(f)` を返します。
`f[0]=0` が必要です。

### `poly pow(long long m, int deg = -1) const`

`f^m` を返します。

### `optional<poly> sqrt(int deg = -1) const`

平方根が存在すれば返します。
なければ `nullopt` です。

### `pair<poly,poly> div(poly g) const`

多項式除算を行い、`{商,余り}` を返します。

### `poly div_only(poly g) const`

商だけ返します。

### `poly substitute(mint v)`

`f(x)` を `f(vx)` に変換します。

## 補助関数

### `to_fps`
### `to_vec`

`vector<mint>` と `FormalPowerSeries<mint>` を相互変換します。

### `all_prod`

複数多項式の総積を返します。

### `SubproductTree`

多点評価用の積木です。

## 使用例

```cpp
#include "math/fps.hpp"
#include "math/static-mod-int.hpp"

using mint=StaticModInt<998244353>;
using FPS=FormalPowerSeries<mint>;

FPS f={1,2,3};
FPS g={4,5};

auto h=f*g;
auto inv=f.inv(5);
```

## 注意

- 高速演算のため `mint::get_mod()` が正しく設定された NTT 可能 mod を想定しています。
- `log`, `exp`, `sqrt` には先頭係数に条件があります。
