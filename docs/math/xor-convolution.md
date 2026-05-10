---
title: XOR Convolution
documentation_of: ../../math/xor-convolution.hpp
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

## 使用例

```cpp
#include "math/xor-convolution.hpp"

using mint = StaticModInt<998244353>;

vc<mint> a = {1,2,3,4};
vc<mint> b = {1,0,1,0};

auto c = xor_convolution(a, b);
// c[k] = sum of a[i]*b[j] for all i^j==k
```

## 注意

- `fwht` に渡す配列は長さが **2 のべき乗** である必要があります（`xor_convolution` は自動調整します）。
- `xor_convolution` の返り値の長さは $\max(|A|, |B|)$ 以上の最小の2のべき乗です。
