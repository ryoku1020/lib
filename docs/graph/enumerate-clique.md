---
title: enumerate-clique
documentation_of: ../../graph/enumerate-clique.hpp
---

# enumerate-clique

無向グラフ中のすべてのクリークを列挙します。

## 関数

### `void enumerate_clique(const G& g, F f)`

各クリーク `vc<int>` に対して `f(clique)` を呼びます。
`clique` の要素は頂点番号の集合です（順序は未定義）。

- `G` — 無向グラフ型（`G::directed() == false` が必要）
- `F` — `void(const vc<int>&)` 相当のコールバック
- 計算量: `O(3^(n/3))` （全クリーク列挙の理論上限）

## 境界・注意

- 無向グラフのみ対応しています（有向グラフを渡すと `static_assert` で失敗）。
- 全クリーク列挙のため、密グラフでは指数的に遅くなります。
- 最大クリークのみが必要な場合はこの関数で全列挙が最もシンプルですが、頂点数が大きい場合は専用アルゴリズムを検討してください。

## 使用例

```cpp
#include "graph/enumerate-clique.hpp"

// 無向グラフを構築
Graph<int,false> g(n);
g.add_edge(0,1,1);
g.add_edge(1,2,1);
g.add_edge(0,2,1);

int max_clique = 0;
enumerate_clique(g, [&](const vc<int>& cl){
    chmax(max_clique, (int)cl.size());
});
// max_clique == 3
```

