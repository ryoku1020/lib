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

## 計算量

`M` を演算に現れる分子・分母の絶対値の最大値とします。

- `reduce_always=true` の構築・四則演算・`reduce`: `O(log M)`（最大公約数計算）
- `reduce_always=false` の構築・四則演算: `O(1)` 回の `T` 上の演算
- 比較・`inv`・`val`: `O(1)` 回の `T` 上の演算
- 追加メモリ: `O(1)`

固定長整数型では、ここでの計算量は各整数演算を `O(1)` と数えています。

## 境界・注意

- 分母 0 は許されません（コンストラクタと `reduce` に `assert` あり）。`inv()` は分子が 0 でない場合に限り、0 による除算もできません。
- 分母は常に正になるよう符号が調整されます。`reduce_always=true` なら既約分数になり、0 は `0/1` になります。
- `reduce_always=false` では内部表現が未約分でも比較できます。
- `T` の範囲を超える演算は検出されません。`long long` の比較では交差積に `__int128` を使いますが、分子・分母を更新する四則演算自体は `long long` の範囲内である必要があります。
- `T` には符号付き整数と同様の四則演算、剰余、比較が必要です。

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
