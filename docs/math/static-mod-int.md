---
title: static_modint
documentation_of: ../../math/modular/static-mod-int.hpp
---

# static_modint

コンパイル時定数 mod の modint です。

## 型

### `static_modint<mod>`

`mod` をテンプレート引数で与えます。
`1<=mod<=2^31-1` を満たす必要があります。

```cpp
using mint=static_modint<998244353>;
```

## 主なメソッド

### `mint(ll x)`

整数 `x` から mod を取って作ります。

### `static constexpr uint32_t get_mod()`

mod を返します。

### `static mint raw(int x)`

`0<=x<mod` を仮定してそのまま格納します。
正規化や上端の検査は行いません。

### `mint.pow(long long n)`

`n` 乗を返します。

### `mint.inv()`

乗法逆元を拡張 Euclid で返します。

## 演算

- `+`, `-`, `*`, `/`
- `+=`, `-=`, `*=`, `/=`
- `==`, `!=`
- 入出力演算子

## 計算量

- `+`, `-`, `*`, コンストラクタ, `raw`: `O(1)`
- `pow(n)`: `O(log n)`
- `inv()` と `/`: `O(log mod)`
- いずれも追加メモリは `O(1)`

## 境界・注意

- `mod` はコンパイル時定数で、`1 <= mod <= 2^31-1` が必要です（`static_assert` あり）。素数である必要はありません。
- `raw(x)` は `0 <= x < mod` のときだけ使えます。実装の `assert` は `x >= 0` しか検査しません。
- `pow(n)` は `n >= 0` を前提とします。
- `inv()` と除算は値が `mod` と互いに素な場合だけ有効です。特に 0 では使えません。`LOCAL` 定義時だけ互いに素かを `assert` します。
- `conv` や `fps` と組み合わせるときは NTT friendly mod を使うのが基本です。

## 使用例

```cpp
#include "math/modular/static-mod-int.hpp"

using mint=static_modint<998244353>;

mint a=3,b=7;
mint c=a*b+b.inv();
cout<<c<<"\n";
```
