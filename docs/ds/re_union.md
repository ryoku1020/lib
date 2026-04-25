---
title: RectangleUnion
documentation_of: ../../ds/re_union.hpp
---

# RectangleUnion

軸平行長方形の和集合面積を求めるスイープライン補助です。

## 型

### `RectangleUnion<T>`

座標型を `T` にします。

## メソッド

### `void ru.reserve(int n)`
### `void ru.add_rectangle(T l, T r, T d, T u)`

長方形 `[l,r) x [d,u)` を追加します。

### `template<class T2> T2 ru.calc()`

和集合面積を返します。

## 使用例

```cpp
RectangleUnion<long long> ru;
ru.add_rectangle(l,r,d,u);
auto area=ru.calc<long long>();
```
