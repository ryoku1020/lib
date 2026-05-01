---
title: Graph Utility
documentation_of: ../../graph/graph-utillity.hpp
---

# Graph Utility

最短路 1 本の復元と、閉路 1 個の検出を行う補助関数です。

## `shortest_path`

### `pair<vc<int>,T> shortest_path(const Graph& g, int s, int t)`

Dijkstra 法で `s` から `t` への最短路を求めます。
返り値は `{path,dist}` です。

- `path`
  頂点列。到達不能なら空
- `dist`
  最短距離

- 制約: 辺重みは非負
- 計算量: `O((V+E)log V)`

## 使用例

```cpp
#include "graph/graph-utillity.hpp"

auto [path,dist]=shortest_path<long long>(g,s,t);
if(path.empty()){
    // unreachable
}
```

## `cycle_detection`

### `pair<vc<int>,vc<int>> cycle_detection(const Graph& g)`

グラフ中の閉路を 1 つ返します。
返り値は `{vertices,edge_ids}` です。
閉路がないときは両方空です。

- 計算量: `O(V+E)`

## 使用例

```cpp
auto [vs,es]=cycle_detection(g);
if(!vs.empty()){
    // cycle found
}
```

## 注意

- `shortest_path` では `e.to`, `e.cost`, `e.from` を参照します。
- `cycle_detection` では `e.to`, `e.id` を参照します。
