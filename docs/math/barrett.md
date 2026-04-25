---
title: Barrett
documentation_of: ../../math/barrett.hpp
---

# Barrett

Barrett reduction による高速 mod 乗算補助です。
`DynamicModInt` の内部で使われています。

## 型

### `Barrett`

## メソッド

### `void b.set(int mod)`

法 `mod` を設定します。

### `unsigned b.reduce(uint64_t x)`

`x mod mod` を高速に返します。

## 使用例

```cpp
#include "math/barrett.hpp"

Barrett b;
b.set(1000000007);
auto r=b.reduce(1234567890123ULL);
```

## 注意

- 単独で使うより `DynamicModInt` の内部利用が主用途です。
