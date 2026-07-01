---
title: Mod Math
documentation_of: ../../math/mod.hpp
---

# Mod Math

組み合わせ計算・合同方程式・mod 平方根をまとめた補助ライブラリです。

## `Binom<mint>`

`mint` 型上で二項係数・順列・重複組合せを計算します。

### `static void Binom<mint>::build(int n)`

`0!` から `n!` までの階乗と逆階乗を前計算します。

- 計算量: `O(n)`

### `static mint Binom<mint>::C(int a, int b)`

`aCb`（二項係数）を返します。
`b < 0`, `b > a`, `a < 0` のとき `0` を返します。

### `static mint Binom<mint>::iC(int a, int b)`

`1 / aCb`（二項係数の逆数）を返します。
`b < 0`, `b > a`, `a < 0` のとき `0` を返します。

### `static mint Binom<mint>::P(int a, int b)`

`aPb`（順列）を返します。
`b < 0`, `b > a`, `a < 0` のとき `0` を返します。

### `static mint Binom<mint>::H(int a, int b)`

`aHb`（重複組合せ、= `C(a+b-1, b)`）を返します。

## `pair<T,T> inv(T x, T m)`

`x` の `mod m` 逆元情報を拡張 Euclid で返します。
返り値 `{a, m'}` は `a * x ≡ 1 (mod m')` に対応します。

---

## `pair<T,T> mod_solve(T a, T b, T m)`

合同方程式 `a*x ≡ b (mod m)` を解きます。

- 解が存在するとき `{x, m'}` を返します。すべての解は `x + k*m'`（k は整数）。
- 解が存在しないとき `{-1, -1}` を返します。
- 計算量: `O(log m)`

```cpp
auto [x, mod2] = mod_solve(a, b, m);
if (x != -1) {
    // x, x + mod2, x + 2*mod2, ... が全解
}
```

---

## `int64_t mod_sqrt(int64_t a, int64_t p)`

`x^2 ≡ a (mod p)` を満たす `x` を 1 つ返します。
存在しないとき `-1` を返します。

- 制約: `0 <= a < p`, `p` は奇素数
- 計算量: `O(log^2 p)`（Tonelli-Shanks）

```cpp
long long r = mod_sqrt(a, p);
if (r != -1) {
    // r * r ≡ a (mod p)
    // もう一方の解は p - r
}
```

## 境界・注意

- `Binom<mint>::C` / `P` / `H` は `build` で前計算したサイズを超えると動作未定義です。十分大きく `build` してください。
- `Binom<mint>::C` は内部テーブルを自動拡張する実装になっています（必要なら `build` を省略可能）。

## 使用例

```cpp
#include "math/mod.hpp"
#include "math/static-mod-int.hpp"

using mint = StaticModInt<998244353>;

Binom<mint>::build(2000000); // 必要な最大値を渡す
auto c = Binom<mint>::C(n, k); // nCk
auto ic = Binom<mint>::iC(n, k); // 1 / nCk
auto p = Binom<mint>::P(n, k); // nPk
auto h = Binom<mint>::H(n, k); // nHk
```
