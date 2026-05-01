---
title: XOR Convolution
documentation_of: ../../math/xor-convolution.hpp
---

# XOR Convolution

ビットごとの XOR 演算に対する畳み込み (Bitwise XOR Convolution) を計算します。
長さが $N, M$ の数列 $A, B$ が与えられたとき、$C_k = \sum_{i \text{ XOR } j = k} A_i B_j$ となる数列 $C$ を高速ウォルシュ・アダマール変換 (Fast Walsh-Hadamard Transform, FWHT) を用いて $O(L \log L)$ で計算します（ただし $L$ は $\max(N, M)$ 以上の最小の2のべき乗）。

## fwht

```cpp
template<class mint>
void fwht(vc<mint>& a, bool is_inv);
```

### 制約・引数
- 配列 `a` の長さは 2 のべき乗である必要があります。
- `is_inv`: `false` の場合は順変換、`true` の場合は逆変換を行います。
- `mint` は除算をサポートする Modint 型である必要があります（逆変換時に配列長で割るため、`mint::get_mod()` によるモジュラ演算が前提となります）。

## xor_convolution

```cpp
template<class mint>
vc<mint> xor_convolution(vc<mint> a, vc<mint> b);
```

### 制約・引数
- `class mint`: Modint 型。
- `vc<mint> a, b`: 畳み込みを行う対象の数列。長さが 2 のべき乗でなくても、内部で自動的に必要な2のべき乗の長さにゼロ埋め（resize）されます。

### 戻り値
- 畳み込み結果の数列 `C`。長さは $\max(|A|, |B|)$ 以上の最小の2のべき乗になります。

### 計算量
- $O(L \log L)$ （ただし $L = 2^{\lceil \log_2(\max(|A|, |B|)) \rceil}$）
