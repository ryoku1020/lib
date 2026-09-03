---
title: XOR Convolution
documentation_of: ../../math/convolution/xor-convolution.hpp
---

# XOR Convolution

$C_k = \sum_{i \oplus j = k} A_i B_j$ となる数列 $C$ を高速ウォルシュ・アダマール変換 (FWHT) で計算します。

## 関数

### `void fwht(vc<mint>& a, bool is_inv)`

FWHT の順変換・逆変換をインプレースで行います。

- 制約: `a` の長さが 2 のべき乗であること
- `is_inv = false` で順変換、`true` で逆変換
- `mint` は除算をサポートする Modint 型が必要（逆変換時に配列長で割る）

### `vc<mint> xor_convolution(vc<mint> a, vc<mint> b)`

- 入力の長さが 2 のべき乗でなくても、内部で自動的にゼロ埋めされます
- 返り値: 長さ $L = 2^{\lceil \log_2(\max(|A|, |B|)) \rceil}$ の畳み込み結果
- 計算量: $O(L \log L)$

## 計算量

- `fwht(a, ...)`: 時間 `O(n log n)`、追加メモリ `O(1)`
- `xor_convolution`: `L` を返り値の長さとして時間 `O(L log L)`、入力コピーと返り値を含むメモリ `O(L)`

## 境界・注意

- `fwht` に渡す配列は長さ 1 以上の **2 のべき乗** である必要があります（`xor_convolution` は自動調整します）。違う長さでは範囲外参照が起こり得ます。
- 逆変換では配列長 `n` で割るため、`n` が法上で可逆でなければなりません。
- `xor_convolution` の返り値の長さは $\max(|A|, |B|)$ 以上の最小の2のべき乗です。
- 両入力が空の場合だけ、返り値は空ではなく `{0}`（長さ 1）です。一方だけが空なら、もう一方に合わせた長さのゼロ列になります。
- `mint` は非零の `get_mod()` と加減乗除算を持つ modint 型である必要があります。

## 使用例

```cpp
#include "math/convolution/xor-convolution.hpp"

using mint = static_modint<998244353>;

vc<mint> a = {1,2,3,4};
vc<mint> b = {1,0,1,0};

auto c = xor_convolution(a, b);
// c[k] = sum of a[i]*b[j] for all i^j==k
```
