---
title: FormalPowerSeries
documentation_of: ../../poly/base.hpp
---

# FormalPowerSeries

形式的冪級数です。
NTT を使って積、逆数、対数、指数、冪、平方根などを高速に計算します。

## 型

### `FormalPowerSeries<mint>`

`vector<mint>` を継承した多項式型です。
通常は NTT friendly mod の `static_modint` と組み合わせます。

```cpp
using mint=static_modint<998244353>;
using FPS=FormalPowerSeries<mint>;
```

## 主な演算

- `+`, `-`, `*`
- 定数との `+`, `-`, `*`, `/`
- `<<`, `>>`
  `x^k` のシフト（`f<<k` で `x^k f(x)`、`f>>k` で `f(x)/x^k` の切り捨て）
- `*` の計算量: `O(n log n)`

## 主なメソッド

`deg` 引数は「返す多項式の次数の上限」です。`deg=-1` のとき、`f` の現在のサイズに合わせます。

### `poly pre(int sz) const`

先頭 `sz` 項だけを取ります（`[x^0, x^{sz-1}]`）。

- 計算量: `O(sz)`

### `poly inv(int deg = -1) const`

逆数 `1/f mod x^deg` を返します。

- 制約: `f[0] != 0`（アサートあり）
- 計算量: `O(deg log deg)`

### `poly diff() const`

微分 `f'` を返します。長さは `max(0, |f|-1)` になります。

- 計算量: `O(|f|)`

### `poly integral() const`

積分 `∫f` を返します（定数項 0）。長さは `|f|+1` になります。

- 計算量: `O(|f|)`

### `poly log(int deg = -1) const`

`log(f) mod x^deg` を返します。
内部で `diff`, `inv`, `integral` を使って計算します。

- 制約: `f[0] == 1`（アサートあり）
- 計算量: `O(deg log deg)`

### `poly exp(int deg = -1) const`

`exp(f) mod x^deg` を返します。

- 制約: `f[0] == 0`（アサートあり）
- 計算量: `O(deg log deg)`

### `poly pow(long long m, int deg = -1) const`

`f^m mod x^deg` を返します。

- 制約: `m >= 0`（負は未定義）
- `m == 0` のとき: `{1, 0, ..., 0}` を返す（f がゼロ多項式でも）
- `f` がゼロ多項式かつ `m > 0` のとき: ゼロ多項式を返す
- `f[0] == 0` でも動作します（内部で leading term を抜き出して log/exp を使う）。ただし `f` の最初の非ゼロ係数 `f[i]` があるとき、`m*i >= deg` ならゼロを返します。
- 計算量: `O(deg log deg)`

### `optional<poly> sqrt(int deg = -1) const`

`g^2 ≡ f mod x^deg` となる `g` を返します。
存在しなければ `nullopt` を返します。

- `f[0]` が mod p 上の二次剰余でない場合: `nullopt`
- `f[0] == 0` のとき: `f` の最初の非ゼロ項の次数が奇数なら `nullopt`
- 計算量: `O(deg log deg)`

### `pair<poly,poly> div(poly g) const`

多項式除算を行い、`{商, 余り}` を返します。
`f = 商 * g + 余り` かつ `deg(余り) < deg(g)` が成り立ちます。

### `poly div_only(poly g) const`

商だけ返します。

### `poly substitute(mint v)`

`f(x)` を `f(v*x)` に変換します。
つまり `i` 次係数を `f[i] * v^i` に変換します。

## 補助関数

### `to_fps(vector<mint>)` / `to_vec(FPS)`

`vector<mint>` と `FormalPowerSeries<mint>` を相互変換します。

### `all_prod(vector<poly>)`

複数の多項式の総積を `O(N log^2 N)` で返します（divide and conquer）。

### `subproduct_tree`

多点評価・補間のための積木です。クエリ点が多い場合に利用します。

## 境界・注意

- NTT 可能 mod（`998244353` など）での使用が前提です。任意 mod では `log`, `exp`, `inv` が正しく動きません。
- `deg=-1` はメソッド呼び出し時の `f` のサイズを上限として使います。明示的に截断したい場合は `deg` を指定してください。
- `pow(0)` は f がゼロ多項式でも `{1, 0, ..., 0}` を返します。これは `f^0 = 1` の定義通りです。

## 使用例

```cpp
#include "poly/base.hpp"
#include "math/modular/static-mod-int.hpp"

using mint=static_modint<998244353>;
using FPS=FormalPowerSeries<mint>;

FPS f={1,2,3}; // 1 + 2x + 3x^2
FPS g={4,5};   // 4 + 5x

auto h=f*g;          // 積 mod x^4
auto inv=f.inv(5);   // 1/f mod x^5
auto logf=f.log(5);  // log(f) mod x^5
FPS q={1,1};
auto eq=q.exp(5);    // exp(1+x) mod x^5
auto pw=f.pow(3,5);  // f^3 mod x^5
auto sq=f.sqrt(5);   // g^2 ≡ f mod x^5 となる g (optional)

// 多項式除算
auto [quot,rem]=f.div_only_with_remainder(g);
// または div_only で商だけ
```
