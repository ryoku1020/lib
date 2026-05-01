---
title: AND Convolution
documentation_of: ../../math/and-convolution.hpp
---

# AND Convolution

ビットごとの AND 演算に対する畳み込み (Bitwise AND Convolution) を計算します。
長さが $N, M$ の数列 $A, B$ が与えられたとき、$C_k = \sum_{i \text{ AND } j = k} A_i B_j$ となる数列 $C$ を高速ゼータ変換 (Fast Zeta Transform)・高速メビウス変換 (Fast Mobius Transform) を用いて $O(L \log L)$ で計算します（ただし $L$ は $\max(N, M)$ 以上の最小の2のべき乗）。

## and_convolution

```cpp
template<class mint>
vc<mint> and_convolution(vc<mint> a, vc<mint> b);
```

### 制約・引数
- `class mint`: Modint 型や `long long` などの算術演算が定義された型。
- `vc<mint> a, b`: 畳み込みを行う対象の数列。長さが 2 のべき乗でなくても、内部で自動的に必要な2のべき乗の長さにゼロ埋め（resize）されます。

### 戻り値
- 畳み込み結果の数列 `C`。長さは $\max(|A|, |B|)$ 以上の最小の2のべき乗になります。

### 計算量
- $O(L \log L)$ （ただし $L = 2^{\lceil \log_2(\max(|A|, |B|)) \rceil}$）
