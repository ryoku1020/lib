---
title: Roll
documentation_of: ../../ds/Hash.hpp
---

# Roll

複数 base 対応の rolling hash です。
文字列や整数列の部分列ハッシュを `O(1)` で取れます。

## 型

### `Roll<base_count>`

`base_count` 本の base を使います。

## 事前設定

### `static void Roll<base_count>::init(int MAXN)`

最大長 `MAXN` までの base 累乗と逆元を前計算します。
先に必須です。

## コンストラクタ

### `Roll(string s)`
### `Roll(vc<int> v)`
### `Roll(vc<ll> v)`

列から rolling hash を構築します。

## メソッド

### `array<ll,base_count> get(int l, int r)`

半開区間 `[l,r)` のハッシュを返します。

- 計算量: `O(base_count)`

## 使用例

```cpp
#include "ds/Hash.hpp"

Roll<2>::init(n);
Roll<2> rh(s);

if(rh.get(l1,r1)==rh.get(l2,r2)){
    // probably equal
}
```

## 注意

- 実装中の include 名は [math/mod261.hpp](/Users/ryoku_/Desktop/cp/lib/math/mod261.hpp) と実ファイル名に差がありますが、型自体は `Mod261Int` を使っています。
