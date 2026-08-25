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

## 境界・注意

- 単独で使うより `dynamic_modint` の内部利用が主用途です。

## 使用例

```cpp
#include "math/modular/barrett.hpp"

barrett b;
b.set(1000000007);
auto r=b.reduce(1234567890123ULL);
```
