---
title: enumerate_clique
documentation_of: ../../graph/enumerate_clique.hpp
---

# enumerate_clique

無向グラフ中のクリークを列挙します。

## 関数

### `void enumerate_clique(const G& g, F f)`

各クリーク `vc<int>` に対して `f(clique)` を呼びます。

## 使用例

```cpp
#include "graph/enumerate_clique.hpp"

enumerate_clique(g,[&](const vector<int>& cl){
    // use clique
});
```

## 注意

- 無向グラフ前提です。
- 全クリーク列挙なので、密グラフでは指数的に増えます。
