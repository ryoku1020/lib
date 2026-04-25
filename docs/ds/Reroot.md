---
title: Redp (Rerooting DP)
documentation_of: ../../ds/Reroot.hpp
---

# Redp (Rerooting DP)

全方位木 DP のテンプレートです。

## 要件

```cpp
struct Reroot{
    using V=...;
    using E=...;
    static E merge(E a,E b);
    static V put_vertex(E a,int v);
    static E put_edge(V a,int e);
    static E id();
};
```

## 型

### `Redp<Reroot>`

## 主なメソッド

### `Redp(int n)`
### `void add_edge(int a, int b, int idx, int xdi)`
### `vc<V> calc()`

`calc()` は各頂点を根とした答えを返します。

## 使用例

```cpp
Redp<Reroot> dp(n);
dp.add_edge(u,v,idx_uv,idx_vu);
auto ans=dp.calc();
```
