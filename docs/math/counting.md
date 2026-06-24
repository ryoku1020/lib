---
title: counting
documentation_of: ../../math/counting.hpp
---

# counting

集合 `s = {s[0], s[1], ..., s[k-1]}` の各要素を「使える個数に制限のある素材」として見たとき、
重み `x^{s[i]}` の積の母関数の係数列を求める関数群です。

内部で形式的冪級数（`fps.hpp`）の `exp` を使っています。

## 関数

### `vc<mint> EnumarateProd(vc<int> s, int size)`

$$\prod_{i} (1 + x^{s_i})$$

の `[x^0, x^1, ..., x^{size-1}]` の係数列を返します。

各要素 `s[i]` を「0 個か 1 個だけ使う」場合の数え上げに対応します。
例えば `s = {2, 3, 5}` のとき、`k` 個の部分集合の重み合計が `w` になる場合の数が `[x^w]` の係数です。

- 計算量: `O(size log size)`

### `vc<mint> EnumarateProdInv(vc<int> s, int size)`

$$\prod_{i} \frac{1}{1 - x^{s_i}}$$

の `[x^0, x^1, ..., x^{size-1}]` の係数列を返します。

各要素 `s[i]` を「何個でも使える」場合の数え上げに対応します（多重集合の個数）。

- 計算量: `O(size log size)`

### `vc<mint> PartitionFunction(int n)`

$$\prod_{k=1}^{n} \frac{1}{1 - x^k}$$

の `[x^0, x^1, ..., x^n]` の係数列を返します。

`[x^w]` の係数は `w` の **分割数** です（整数 `w` を正整数の和で表す方法の数）。

- 計算量: `O(n log n)`

## アルゴリズム

形式的冪級数の対数を取ってから `exp` に通します。

`EnumarateProd` の場合、`cnt[i]` を `s` 中で値 `i` が出現する回数とすると:

$$\log \prod_i (1+x^i)^{cnt[i]} = \sum_i cnt[i] \log(1+x^i)$$

$\log(1+x^i) = \sum_{j \geq 1} (-1)^{j-1} \frac{x^{ij}}{j}$ を展開して係数を集め、`exp` を適用します。

`EnumarateProdInv` も同様で、$\log(1/(1-x^i)) = \sum_{j \geq 1} \frac{x^{ij}}{j}$ を使います。

## 境界・注意

- `mint` は `fps.hpp` で定義されている静的 mod 整数型です。
- `size` は「係数列の長さ」です。`[x^0]` から `[x^{size-1}]` までを返します。
- `EnumarateProd` / `EnumarateProdInv` は `s` 中に重複があっても正しく処理します（`cnt` で集計するため）。
- `PartitionFunction(0)` は `{1}` を返します（分割数 `p(0) = 1` の定義通り）。

## 使用例

### 0/1 ナップサック問題（母関数）

サイズ `s[i]` のアイテムを 1 個ずつ選ぶとき、合計サイズが `W` になる選び方の数:

```cpp
#include "math/counting.hpp"

vc<int> s = {2, 3, 5, 7};
auto f = EnumarateProd(s, W + 1);
cout << f[W] << "\n"; // 合計サイズ W になる選び方の数
```

### 無制限ナップサック問題（母関数）

サイズ `s[i]` のアイテムを何個でも選ぶとき、合計サイズが `W` になる選び方の数:

```cpp
auto f = EnumarateProdInv(s, W + 1);
cout << f[W] << "\n";
```

### 分割数

```cpp
auto f = PartitionFunction(N);
// f[w] = w の分割数 (w = 0, 1, ..., N)
cout << f[N] << "\n";
```

