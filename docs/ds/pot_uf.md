---
title: PotentializedUnionFind
documentation_of: ../../ds/pot_uf.hpp
---

# PotentializedUnionFind

重み付き Union-Find です。
各頂点のポテンシャル差を管理します。

## 要件

```cpp
struct X{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type inv(value_type a);
    static value_type e();
};
```

## コンストラクタ

### `PotentializedUnionFind<X>(int n)`

## メソッド

### `int uf.root(int x)`
### `int uf.same(int x, int y)`

### `value_type uf.diff(int x, int y)`

同一成分内での差 `val[x]^{-1} * val[y]` を返します。

### `int uf.merge(int x, int y, value_type W)`

`val[x] = val[y] * W` となるように併合します。

- 整合して新規併合: `1`
- 既存条件と矛盾なし: `0`
- 矛盾: `-1`

## 使用例

```cpp
PotentializedUnionFind<X> uf(n);
uf.merge(x,y,w);
auto d=uf.diff(x,y);
```
