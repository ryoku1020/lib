---
title: prefix_multicative helpers
documentation_of: ../../math/prefix_multicative.hpp
---

# prefix_multicative helpers

素数ごとの寄与をまとめて扱う前計算補助です。
`lucy_dp` や `black_algorithm` が入っています。

## 関数

### `vc<ll> floors(ll n)`

`floor(n/k)` が取りうる値を昇順で返します。

### `tuple<vc<T>,vc<int>,vc<ll>> lucy_dp(ll n, F f, G g)`

Lucy DP を行い、DP 値・素数列・`floors(n)` を返します。

### `mint black_algorithm(ll n, F f, G g, H h)`

積性的関数系の高速総和を行う補助です。

## 注意

- かなり上級者向けの補助関数群です。
- 実際の `f`, `g`, `h` の設計は呼び出し側問題設定に依存します。
