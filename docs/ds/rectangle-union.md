---
title: RectangleUnion
documentation_of: ../../ds/rectangle-union.hpp
---

# RectangleUnion

軸平行長方形の和集合の面積をスイープラインで計算します。

## 型

```cpp
RectangleUnion<T>
```

- `T` — 座標の型（`long long` など）

## メソッド

### `void ru.reserve(int n)`

`n` 個の長方形を追加することを事前に通知してメモリ確保します。任意。

### `void ru.add_rectangle(T l, T r, T d, T u)`

長方形 `[l, r) × [d, u)` を追加します。

- 制約: `l < r` かつ `d < u`（等号はアサートで停止）

### `template<class T2> T2 ru.calc()`

追加した全長方形の和集合の面積を返します。
`T2` には面積を収められる型（通常 `long long`）を指定します。

- 計算量: `O(n log n)`（n は追加した長方形の数）

## 使用例

```cpp
#include "ds/rectangle-union.hpp"

RectangleUnion<long long> ru;
ru.add_rectangle(0, 3, 0, 2); // [0,3)×[0,2)
ru.add_rectangle(1, 4, 1, 3); // [1,4)×[1,3)

auto area = ru.calc<long long>(); // 和集合の面積
```

## 注意

- `l < r` かつ `d < u` が必須です（等号は `assert` で停止）。
- `calc<T2>()` は何度でも呼べますが、毎回 `O(n log n)` かかります。
- 内部で座標圧縮とセグメント木を使います。
