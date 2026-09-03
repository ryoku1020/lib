---
title: counting
documentation_of: ../../math/combinatorics/counting.hpp
---

# counting

集合 `s = {s[0], s[1], ..., s[k-1]}` の各要素を「使える個数に制限のある素材」として見たとき、
重み `x^{s[i]}` の積の母関数の係数列を求める関数群です。

内部で形式的冪級数（`poly/base.hpp`）の `exp` を使っています。

## 関数

### `vc<mint> enumarate_prod(vc<int> s, int size)`

$$\prod_{i} (1 + x^{s_i})$$

の `[x^0, x^1, ..., x^{size-1}]` の係数列を返します。

各要素 `s[i]` を「0 個か 1 個だけ使う」場合の数え上げに対応します。
例えば `s = {2, 3, 5}` のとき、`k` 個の部分集合の重み合計が `w` になる場合の数が `[x^w]` の係数です。

- 計算量: `O(max(s)+size log size)`

### `vc<mint> enumarate_prod_inv(vc<int> s, int size)`

$$\prod_{i} \frac{1}{1 - x^{s_i}}$$

の `[x^0, x^1, ..., x^{size-1}]` の係数列を返します。

各要素 `s[i]` を「何個でも使える」場合の数え上げに対応します（多重集合の個数）。

- 計算量: `O(max(s)+size log size)`

### `vc<mint> partition_function(int n)`

$$\prod_{k=1}^{n} \frac{1}{1 - x^k}$$

の `[x^0, x^1, ..., x^n]` の係数列を返します。

`[x^w]` の係数は `w` の **分割数** です（整数 `w` を正整数の和で表す方法の数）。

- 計算量: `O(n log n)`

## アルゴリズム

形式的冪級数の対数を取ってから `exp` に通します。

`enumarate_prod` の場合、`cnt[i]` を `s` 中で値 `i` が出現する回数とすると:

$$\log \prod_i (1+x^i)^{cnt[i]} = \sum_i cnt[i] \log(1+x^i)$$

$\log(1+x^i) = \sum_{j \geq 1} (-1)^{j-1} \frac{x^{ij}}{j}$ を展開して係数を集め、`exp` を適用します。

`enumarate_prod_inv` も同様で、$\log(1/(1-x^i)) = \sum_{j \geq 1} \frac{x^{ij}}{j}$ を使います。

## 計算量

`S = max(s)`、返す係数列の長さを `size` とします。

- `enumarate_prod`, `enumarate_prod_inv`: 時間 `O(S+size log size)`、メモリ `O(S+size)`
- `partition_function(n)`: 時間 `O(n log n)`、メモリ `O(n)`

形式的冪級数の `exp` が NTT により `O(size log size)` で動く場合の計算量です。`s` に `size` より非常に大きい値がある場合も、現在の実装は長さ `S+1` の頻度配列を確保します。

## 境界・注意

- `mint` は `poly/base.hpp` で定義されている静的 mod 整数型です。
- `size` は「係数列の長さ」です。`[x^0]` から `[x^{size-1}]` までを返します。
- `enumarate_prod` / `enumarate_prod_inv` では `size >= 1`、全ての `s[i] > 0` が必要です。実装は `size >= 0` を検査しますが、`size == 0` では内部の `exp(0)` が空 FPS を参照します。
- `enumarate_prod` / `enumarate_prod_inv` は `s` 中に重複があっても正しく処理します（`cnt` で集計するため）。
- 空の `s` と正の `size` に対しては `{1,0,...,0}` を返します。
- `1` から `size` 程度までの整数が法上で可逆であり、必要な長さの NTT が可能でなければなりません。通常は `static_modint<998244353>` を使います。
- `partition_function(0)` は `{1}` を返します（分割数 `p(0) = 1` の定義通り）。

## 使用例

### 0/1 ナップサック問題（母関数）

サイズ `s[i]` のアイテムを 1 個ずつ選ぶとき、合計サイズが `W` になる選び方の数:

```cpp
#include "math/combinatorics/counting.hpp"

vc<int> s = {2, 3, 5, 7};
auto f = enumarate_prod(s, W + 1);
cout << f[W] << "\n"; // 合計サイズ W になる選び方の数
```

### 無制限ナップサック問題（母関数）

サイズ `s[i]` のアイテムを何個でも選ぶとき、合計サイズが `W` になる選び方の数:

```cpp
auto f = enumarate_prod_inv(s, W + 1);
cout << f[W] << "\n";
```

### 分割数

```cpp
auto f = partition_function(N);
// f[w] = w の分割数 (w = 0, 1, ..., N)
cout << f[N] << "\n";
```
