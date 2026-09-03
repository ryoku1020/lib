---
title: bostan_mori
documentation_of: ../../poly/bostan-mori.hpp
---

# bostan_mori

有理型母関数 `P(x) / Q(x)` の `x^n` 係数を高速に求めます。

## 関数

### `mint bostan_mori(fps<mint> p, fps<mint> q, long long n)`

`P(x)/Q(x)` の `x^n` 係数を返します。

- 計算量: `O(d log d log(n+1))` 程度

ここで `d = q.size()`（`Q` の次数 + 1）です。

## 計算量

`d = q.size()`、`z` を `2*d` 以上の最小の 2 のべき乗とすると、時間 `O(z log z log(n+1))`、メモリ `O(z)` です。
通常は `O(d log d log(n+1))` と表します。

## 境界・注意

- `poly/base.hpp` と NTT 環境に依存します。
- `q[0] != 0` が必要です（アサートあり）。
- `n >= 0` が必要です（アサートあり）。
- `p` または `q` が空なら `0` を返します。
- 非空の `p` を処理するときは `q.size() >= 2` が必要です。定数多項式 `Q`（`q.size() == 1`）では内部で `p` が空になり、最後の `p[0]` 参照が不正になります。
- `p.size() >= q.size()` の場合、実装は `p` を先頭 `q.size()-1` 項へ切り詰めます。多項式部分も含む一般の `P/Q` が欲しい場合は、事前に多項式除算してください。
- `z` 点 NTT が可能で、`z` と `z/2` が法上で可逆な `mint` が必要です。通常は `static_modint<998244353>` などの NTT friendly な素数法を使います。
- 最後に `p[0]/q[0]` を計算するため、`q[0]` の逆元が存在する必要があります。

## 使用例

```cpp
#include "poly/bostan-mori.hpp"

using mint=static_modint<998244353>;
using FPS=fps<mint>;

FPS p={0,1};    // x
FPS q={1,-1,-1}; // 1-x-x^2

mint fn=bostan_mori(p,q,n);
```
