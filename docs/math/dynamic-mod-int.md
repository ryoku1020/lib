---
title: dynamic_modint
documentation_of: ../../math/modular/dynamic-mod-int.hpp
---

# dynamic_modint

実行時に mod を設定する modint です。

## 型

### `dynamic_modint<id>`

`id` が違えば別の静的領域を使うので、複数 mod を同時に持てます。

## 事前設定

### `static void mint::set_mod(int md)`

先に mod を設定します。
`1<=md<=2^31-1` を満たす必要があります。

```cpp
using mint=dynamic_modint<0>;
mint::set_mod(998244353);
```

## 主なメソッド

### `mint(ll x)`

整数 `x` から mod を取って作ります。

### `static mint raw(int x)`

`0<=x<mod` を仮定してそのまま格納します。
この範囲への正規化や上端の検査は行いません。

### `static int& get_mod()`

現在の mod を返します。

### `mint.pow(long long n)`

`n` 乗を返します。

### `mint.inv()`

逆元を返します。
`gcd(mint.val, mod) == 1` を仮定します。

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

- `set_mod` 前に、整数からの構築・乗除算など法を参照する操作をしてはいけません。
- `set_mod(md)` は `1 <= md <= 2^31-1` を要求します。
- 同じ `id` の全インスタンスは法を共有します。既存の値を保持したまま法を変更すると、その値の意味も変わるため、法の変更後は値を作り直してください。
- `raw(x)` は `0 <= x < mod` のときだけ使えます。実装の `assert` は `x >= 0` しか検査しません。
- `pow(n)` は `n >= 0` を前提とします。
- `inv()` と除算は、対象が法と互いに素な場合だけ有効です。特に 0 では使えません。合成数を法にしても、互いに素なら逆元を計算できます。

## 使用例

```cpp
#include "math/modular/dynamic-mod-int.hpp"

using mint=dynamic_modint<0>;
mint::set_mod(1000000007);

mint a=2,b=5;
mint c=a.pow(10)+b;
mint d=c/b;
cout<<d<<"\n";
```
