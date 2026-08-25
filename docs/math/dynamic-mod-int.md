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

### `static int& get_mod()`

現在の mod を返します。

### `mint.pow(long long n)`

`n` 乗を返します。

### `mint.inv()`

逆元を返します。
存在することを仮定します。

## 演算

- `+`, `-`, `*`, `/`
- `+=`, `-=`, `*=`, `/=`
- `==`, `!=`
- 入出力演算子

## 境界・注意

- `set_mod` 前に使ってはいけません。
- `inv()` は `gcd(val,mod)=1` を仮定します。

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
