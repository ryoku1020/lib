---
title: barrett
documentation_of: ../../math/modular/barrett.hpp
---

# barrett

barrett reduction による高速 mod 乗算補助です。
`dynamic_modint` の内部で使われています。

## 型

### `barrett`

## メソッド

### `void b.set(int mod)`

法 `mod` を設定します。

### `unsigned b.reduce(uint64_t x)`

`x mod mod` を高速に返します。

## 計算量

- `set`, `reduce`: 時間 `O(1)`、追加メモリ `O(1)`

## 境界・注意

- `set` の `mod` は正でなければなりません（`assert` あり）。
- `reduce` より前に、同じインスタンスへ `set` を 1 回以上呼ぶ必要があります。
- `reduce` は任意の `uint64_t` を受け取れます。返り値は常に `[0, mod)` です。
- 法を変える場合は、再度 `set` を呼びます。
- 単独で使うより `dynamic_modint` の内部利用が主用途です。

## 使用例

```cpp
#include "math/modular/barrett.hpp"

barrett b;
b.set(1000000007);
auto r=b.reduce(1234567890123ULL);
// r == 567881485
```
