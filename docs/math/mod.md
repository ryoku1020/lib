---
title: Mod Math
documentation_of: ../../math/modular/mod-utillity.hpp
---

# Mod Math

組み合わせ計算・合同方程式・mod 平方根をまとめた補助ライブラリです。

## `binom<mint>`

`mint` 型上で二項係数・順列・重複組合せを計算します。

### `static void binom<mint>::build(int n)`

`0!` から `n!` までの階乗と逆階乗を前計算します。

- 計算量: `O(n)`

### `static mint binom<mint>::C(int a, int b)`

`aCb`（二項係数）を返します。
`b < 0`, `b > a`, `a < 0` のとき `0` を返します。

### `static mint binom<mint>::iC(int a, int b)`

`1 / aCb`（二項係数の逆数）を返します。
`b < 0`, `b > a`, `a < 0` のとき `0` を返します。

### `static mint binom<mint>::P(int a, int b)`

`aPb`（順列）を返します。
`b < 0`, `b > a`, `a < 0` のとき `0` を返します。

### `static mint binom<mint>::H(int a, int b)`

`aHb`（重複組合せ、= `C(a+b-1, b)`）を返します。

## `pair<T,T> inv(T x, T m)`

`x` の `mod m` 逆元情報を拡張 Euclid で返します。
`g = gcd(x,m)` とすると、返り値 `{a, m/g}` は `a * (x/g) ≡ 1 (mod m/g)` に対応します。
`a` は `0 <= a < m/g` に正規化されます。`g == 1` なら通常の `x` の逆元です。

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

- 制約: `p` は素数
- 計算量: 期待 `O(log p)` 回の mod 演算（ランダム化された Cipolla 法）

```cpp
long long r = mod_sqrt(a, p);
if (r != -1) {
    // r * r ≡ a (mod p)
    // もう一方の解は p - r
}
```

## 計算量

- `binom::build(n)`: 初めて `n` まで伸ばす部分について時間 `O(n)`、静的テーブルのメモリ `O(n)`
- `C`, `iC`, `P`, `H`: 必要な表が構築済みなら `O(1)`。未構築なら自動拡張分を含めて償却 `O(1)` / 1 回の拡張 `O(n)`
- `inv`, `mod_solve`: 時間 `O(log m)`、追加メモリは再帰スタック `O(log m)`
- `mod_sqrt`: 期待時間 `O(log p)` 回の mod 演算、追加メモリ `O(1)`

## 境界・注意

- `binom` の各アクセサと `C` / `P` / `H` は内部テーブルを自動拡張するため、`build` は省略できます。
- `get_mod()` を持つ `mint` では、通常は素数法かつ必要な最大添字 `n < mod` が必要です。`dynamic_modint` は先に法を設定してください。法を変更するとテーブルは自動で作り直されます。
- `C(a,b)` / `iC(a,b)` は範囲外なら通常 0 ですが、`b == 0` は先に処理されるため `C(a,0) == 1` です。通常の組合せ用途では `a,b >= 0` を渡してください。
- `iC(a,b)` は二項係数が法上で非零・可逆な場合だけ、その逆数を表します。
- `inv(x,m)` と `mod_solve(a,b,m)` は `m > 0` の整数型を前提とします。`mod_solve` は解がなければ `{-1,-1}` を返します。
- `inv` はテンプレート関数ですが、内部で `extgcd<ll>` を明示しているため `T = long long` で使ってください。
- `mod_sqrt(a,p)` は `a` を内部で `[0,p)` に正規化します。`2 <= p <= 2^31-1` の素数が必要で、`p == 2` にも対応します。乱数を使うため実行時間は確率的です。

## 使用例

```cpp
#include "math/modular/mod-utillity.hpp"
#include "math/modular/static-mod-int.hpp"

using mint = static_modint<998244353>;

binom<mint>::build(2000000); // 必要な最大値を渡す
auto c = binom<mint>::C(n, k); // nCk
auto ic = binom<mint>::iC(n, k); // 1 / nCk
auto p = binom<mint>::P(n, k); // nPk
auto h = binom<mint>::H(n, k); // nHk
```
