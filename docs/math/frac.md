---
title: frac
documentation_of: ../../math/arithmetic/frac.hpp
---

# frac

有理数を分子 `a`、分母 `b` で持つ構造体です。
加減乗除、比較、符号調整、約分付きの演算をサポートします。

## 使い方

```cpp
#include "math/arithmetic/frac.hpp"

using F=frac<long long>;

F a(2,4);   // 1/2 に約分される
F b(1,6);

auto c=a+b; // 2/3
auto d=a*b; // 1/12
bool ok=(a<b);
```

約分を毎回したくないときは第 2 テンプレート引数を `false` にします。

```cpp
using G=frac<long long,false>;
G x(2,4);   // 2/4 のまま保持
x.reduce(); // ここで約分
```

## テンプレート引数

- `T`
  分子分母の型です。デフォルトは `ll` です。
- `reduce_always`
  `true` のとき演算のたびに約分します。

## 主なメソッド

- `frac(T a=0)`
  整数 `a/1` を作ります。
- `frac(T a,T b)`
  分数 `a/b` を作ります。
- `void reduce()`
  約分して分母の符号を正に揃えます。
- `frac inv() const`
  逆数を返します。
- `ld val() const`
  `long double` に変換した値を返します。

## 演算

- `+`, `-`, `*`, `/`
- `==`, `!=`, `<`, `<=`, `>`, `>=`
- 単項 `+`, `-`
- `abs`

## 境界・注意

- 分母 0 は許されません。
- `reduce_always=false` では内部表現が未約分でも、比較演算は正しく動きます。

## 使用例

傾きや比を誤差なく比較します。

```cpp
using F=frac<long long>;

F a(dy1,dx1);
F b(dy2,dx2);

if(a<b){
    // 1 本目の傾きの方が小さい
}
```
