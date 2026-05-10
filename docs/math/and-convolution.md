---
title: AND Convolution
documentation_of: ../../math/and-convolution.hpp
---

# AND Convolution

$C_k = \sum_{i \mathbin{\&} j = k} A_i B_j$ となる数列 $C$ を高速ゼータ変換・メビウス変換で計算します。

## 関数

### `vc<mint> and_convolution(vc<mint> a, vc<mint> b)`

- `mint` — Modint 型や `long long` など四則演算が定義された型
- 入力の長さが 2 のべき乗でなくても、内部で自動的にゼロ埋めされます
- 返り値: 長さ $L = 2^{\lceil \log_2(\max(|A|, |B|)) \rceil}$ の畳み込み結果
- 計算量: $O(L \log L)$

## 使用例

```cpp
#include "math/and-convolution.hpp"

using mint = StaticModInt<998244353>;

vc<mint> a = {1,2,3,4}; // A[0..3]
vc<mint> b = {1,0,1,0}; // B[0..3]

auto c = and_convolution(a, b);
// c[k] = sum of a[i]*b[j] for all i&j==k
// c[0] = a[0]*b[0] + a[1]*b[0] + a[2]*b[0] + ... など
```

## 注意

- 返り値の長さは $\max(|A|, |B|)$ 以上の最小の2のべき乗になります。
- 添字が $k$ 未満の部分は 0 埋めとして正しく計算されます。
