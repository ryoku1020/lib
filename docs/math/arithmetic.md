---
title: 数値・線形代数 API | sieve / fixed_matrix
documentation_of: ../../math/arithmetic/Number.hpp
keywords: sieve, factorize, mobius, phi, fixed_matrix, characteristic, berlekamp_massey, randf, bint, sint
---

# 数値・線形代数の追加 API

## 篩と整数関数 (`sieve`)

`sieve` は静的共有の最小素因数篩です。

```cpp
#include "math/arithmetic/Number.hpp"

sieve::build(1000000);
auto f = sieve::factorize(360); // {{2,3},{3,2},{5,1}}
int phi = sieve::phi(360);
for (int d : sieve::div(12)) { /* 12 の正の約数 */ }
```

- `build(N)` は `mf[0..N]` を構築・拡張。時間 `O(N log log N)`、領域 `O(N)`。複数関数から共有される。
- `factorize(x)` は `{素因数, 指数}` を昇順で返す。`x>0`。前処理後 `O(log x)`、範囲外なら篩も構築。
- `div(x)` は約数を range-for で列挙する view。`x>0`。約数個数 `τ(x)` 個。
- `mobius(x)`, `is_prime(x)`, `phi(x)` はそれぞれ Möbius 関数・素数判定・Euler φ 関数。`mobius` / `phi` は `x>0`。
- `nom0div(x)` は相異なる素因数の部分積（平方因子を持たない約数）を返す。要素数 `2^ω(x)`。

## Berlekamp–Massey

`berlekamp_massey(S)` は有限体上の数列から最小線形漸化式を推定し `{L,Q}` を返します。`Q[0] == -1` で、`S[n] = sum(i=1..L) Q[i]*S[n-i]` の係数です。

- `mint` は除算可能な modint、列は十分な初期項で、法上で必要な discrepancy が割れること。
- 時間 `O(n^2)`、領域 `O(n)`。
- 返る漸化式は入力有限項を説明する最小次数のものです。別ページの [Bostan–Mori](bostan-mori.md) で n 番目の項へ進めます。

## 行列

- `fixed_matrix<T,N,M>` はコンパイル時固定サイズの行列。`A[i][j]` でアクセス、`trans()`, `+`, `-`, `*` を提供。`N×M` と `M×K` の積は `N×K`。積の時間 `O(NMK)`、メモリ `O(NM)`。
- 正方行列の `unit()`, `pow(k)`, `det()`, `rank()` を提供。`pow(k)` は `k>=0`、`det()` は除算可能な係数体を想定します。`mint` 積算用の最適化では係数 `.val` を持つ型を使います。
- `characteristic(A)` は動的 `matrix<T>` の特性多項式係数列を返します。空行列は `{1}`。計算量 `O(n^3)` 級。実装で pivot 除算を行うため、非零 pivot が可逆な体を使います。
- `hessenberg(A)` は相似変換で上 Hessenberg 形にした行列を返します。入力を値渡しし、元行列を変更しません。

## 補助数値型

- `sint` は2個の固定素数 modint を使い、積 `2147483629 * 2147483647` 未満の整数を保持する residue 型です。`val()` は非負代表を返します。`inv()` / `/` は両方の mod で非零のときだけ定義。
- `bint` は符号付き多倍長整数です。基数は `2^30`、演算は `bint.hpp` の `+,-,*,/,%`。積は畳み込みを利用します。`ll` を越える演算結果を扱えますが、除算は 0 でない divisor が必要です。
- `randf` は `operator()()` で `ull`、`operator()(l,r)` で `[l,r)` の一様整数を返します。各インスタンスは時計 seed の `mt19937_64` を持ち、再現性が必要なら `mt` を seed し直します。

関連: [動的 modint](dynamic-mod-int.md) · [行列](mat.md) · [二項係数](advanced.md#二項係数)
