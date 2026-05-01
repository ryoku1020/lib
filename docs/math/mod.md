---
title: Mod Math
documentation_of: ../../math/mod.hpp
---

# Mod Math

組み合わせ計算、合同方程式、mod 平方根をまとめた補助ライブラリです。

## `Binom<mint>`

`mint` 型上で階乗・逆階乗を持ち、`C / P / H` を計算します。

### 要件

- `mint` が四則演算と逆元計算に対応していること

### `void Binom<mint>::build(int n)`

`0!` から `n!` までと、その逆元を前計算します。

- 計算量: `O(n)`

### `mint Binom<mint>::C(int a, int b)`

`aCb` を返します。
条件を満たさないときは `0` を返します。

### `mint Binom<mint>::P(int a, int b)`

`aPb` を返します。

### `mint Binom<mint>::H(int a, int b)`

重複組合せ `aHb` を返します。

## 使用例

```cpp
#include "math/mod.hpp"
#include "math/dynamic-mod-int.hpp"

using mint=DynamicModInt<0>;
mint::set_mod(998244353);

Binom<mint>::build(1000000);
auto c=Binom<mint>::C(n,k);
auto p=Binom<mint>::P(n,k);
auto h=Binom<mint>::H(n,k);
```

## `pair<T,T> inv(T x, T m)`

`x` の `mod m` における逆元に関する情報を返します。
返り値は `{a,m'}` で、`a*x ≡ 1 (mod m')` に対応します。
内部では拡張 Euclid を使っています。

## `pair<T,T> mod_solve(T a, T b, T m)`

合同方程式

`a*x ≡ b (mod m)`

を解きます。

解が存在するとき `{x,m'}` を返し、すべての解は `x + k*m'` と表せます。
存在しないときは `{-1,-1}` を返します。

- 計算量: `O(log m)`

## `int64_t mod_sqrt(int64_t a, int64_t p)`

`x^2 ≡ a (mod p)` を満たす `x` を 1 つ返します。
存在しないときは `-1` を返します。

- 制約: `0<=a<p`, `p` は素数

## 使用例

```cpp
auto [x,mod2]=mod_solve(a,b,m);
if(x!=-1){
    // x + k*mod2 が解
}

long long r=mod_sqrt(a,p);
if(r!=-1){
    // r^2 ≡ a (mod p)
}
```

## 注意

- `Binom<mint>::C` は必要なら内部テーブルを自動拡張します。
- `mod_sqrt` は Tonelli-Shanks 法です。
