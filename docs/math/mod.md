---
title: Mod Math (組み合わせ・モジュロ演算・平方根)
documentation_of: ../../math/mod.hpp
---

# Mod Math (組み合わせ・モジュロ演算・平方根)

モジュロ上での二項係数・順列・重複組合せの計算、およびモジュロ演算に対する一次方程式の解法・平方根の計算を提供するライブラリです。
内部で動的 mod の構造体 (`d_mint.cpp`) を利用しています。

## 使い方

```cpp
#include "math/mod.cpp"

// 組み合わせ計算 (Mint型に依存)
using mint = d_mint<998244353>;

// 前計算として N までの階乗と逆元を用意
Binom<mint>::build(N);

// aCb (組み合わせ)
mint c = Binom<mint>::C(a, b);

// aPb (順列)
mint p = Binom<mint>::P(a, b);

// aHb (重複組合せ)
mint h = Binom<mint>::H(a, b);

// モジュロ 1次方程式 ax ≡ b (mod m) の解 (x, m') を求める
auto [x, m_prime] = mod_solve(a, b, m);

// モジュロ平方根 x^2 ≡ a (mod p) となる x を求める (存在しなければ -1)
int64_t sq = mod_sqrt(a, p);
```

## メソッド

### `Binom<mint>::build(int n)`
階乗 `fact` と 逆元階乗 `invfact` をサイズ $n+1$ まで前計算します。
- 計算量: 初回呼び出し時に $O(N)$。すでに十分なサイズが計算されている場合は $O(1)$。

### `Binom<mint>::C(int a, int b)`
二項係数 $\binom{a}{b}$ を返します。
- 制約: $a \ge b \ge 0$。条件を満たさない場合は $0$ を返します。
- 計算量: $O(1)$ (テーブルが足りない場合は自動的に $O(a)$ かけて拡張されます)

### `Binom<mint>::P(int a, int b)`
順列 $P(a, b) = \frac{a!}{(a-b)!}$ を返します。
- 制約: $a \ge b \ge 0$。条件を満たさない場合は $0$ を返します。
- 計算量: $O(1)$

### `Binom<mint>::H(int a, int b)`
重複組合せ $H(a, b) = \binom{a+b-1}{b}$ を返します。
- 計算量: $O(1)$

### `std::pair<T, T> mod_solve(T a, T b, T m)`
一次合同式 $ax \equiv b \pmod m$ を解きます。
解が存在する場合は、最小の非負の解 $x$ と、新しいモジュロ $m'$ (すなわち、解は $x + k m'$ と表される) のペアを返します。
解が存在しない場合は `{-1, -1}` を返します。
- 計算量: 拡張ユークリッドの互除法による $O(\log m)$

### `int64_t mod_sqrt(const int64_t &a, const int64_t &p)`
Tonelli-Shanks法により、二次合同式 $x^2 \equiv a \pmod p$ となる $x$ を求めます。素数 $p$ が与えられたとして計算します。
- 制約: $0 \le a < p$、$p$ は素数。
- 計算量: $p-1$ が $2$ で割り切れる回数を $e$ として、最悪 $O(e^2)$。平均的には $O(\log p)$。
