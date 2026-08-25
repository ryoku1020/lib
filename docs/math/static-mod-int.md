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

### `mint.pow(long long n)`

`n` 乗を返します。

### `mint.inv()`

逆元を返します。

## 演算

- `+`, `-`, `*`, `/`
- `+=`, `-=`, `*=`, `/=`
- `==`, `!=`
- 入出力演算子

## 境界・注意

- `inv()` は逆元が存在することを仮定します。
- `conv` や `fps` と組み合わせるときは NTT friendly mod を使うのが基本です。

## 使用例

```cpp
#include "math/modular/static-mod-int.hpp"

using mint=static_modint<998244353>;

mint a=3,b=7;
mint c=a*b+b.inv();
cout<<c<<"\n";
```
