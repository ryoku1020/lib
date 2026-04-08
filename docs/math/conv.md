---
title: Convolution (畳み込み)
documentation_of: ../../math/conv.hpp
---

# Convolution (畳み込み)

Number Theoretic Transform (NTT) および高速フーリエ変換を用いた配列の畳み込み計算ライブラリです。
AtCoder Library (ACL) のアルゴリズムをベースに実装されています。

## 使い方

```cpp
#include "math/conv.cpp"

// Modint (静的mod 998244353) の畳み込み
using mint = s_mint<998244353>;
vector<mint> a = {1, 2, 3};
vector<mint> b = {4, 5, 6};
vector<mint> c = convolution(a, b); // c の長さは |a| + |b| - 1

// 任意のモジュロ (または64bit整数) での畳み込み (任意mod NTT)
vector<long long> a2 = {1, 2, 3};
vector<long long> b2 = {4, 5, 6};
long long MOD = 1e9 + 7;
vector<long long> c2 = convolution_ll(a2, b2, MOD);
```

## メソッド

### `std::vector<mint> convolution(const std::vector<mint>& a, const std::vector<mint>& b)`
配列 $a$ と配列 $b$ を NTT 用の素数モジュロ上 (通常は $998244353$) で畳み込みます。
出力される配列 $c$ の長さは $N + M - 1$ ($N = |a|, M = |b|$) であり、$c_k = \sum_{i+j=k} a_i b_j$ となります。
- 制約: モジュロが NTT Friendly であること ($998244353$ や $167772161$ など)。
- 計算量: $O((N+M) \log (N+M))$

### `std::vector<long long> convolution_ll(const std::vector<long long>& a, const std::vector<long long>& b)`
任意の 64bit 整数の配列 $a, b$ の畳み込みを、3つの NTT Friendly な素数上でそれぞれ計算し、Garnerのアルゴリズム (CRT) を用いて復元して返します。
これにより、要素がモジュロに依存しない畳み込みを行えます。
- 制約: 畳み込み後の各要素が最大で $3 \times 10^{18}$ 程度に収まること ($2^{60}$ 未満)。
- 計算量: $O((N+M) \log (N+M))$

### `std::vector<long long> convolution_ll(const std::vector<long long>& a, const std::vector<long long>& b, long long MOD)`
`convolution_ll` の結果の各要素を `MOD` で割った余りを返します。
- 計算量: $O((N+M) \log (N+M))$
