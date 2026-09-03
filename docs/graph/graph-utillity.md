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
  最短距離。到達不能の場合は `T{}`（通常は 0）

- 制約: 辺重みは非負
- 計算量: `O((V+E)log V)`

`s==t` では `{vc<int>{s},T{0}}` を返します。

## `cycle_detection`

### `pair<vc<int>,vc<int>> cycle_detection(const Graph& g)`

グラフ中の閉路を 1 つ返します。
返り値は `{vertices,edge_ids}` です。
閉路がないときは両方空です。

- 計算量: `O(V+E)`

閉路が見つかった場合、`vertices.size()==edge_ids.size()` で、`edge_ids[i]` は `vertices[i]` から `vertices[(i+1)%size]` への辺です。

## 計算量まとめ

- `shortest_path`: `O((V+E)log V)` 時間、`O(V)` 補助領域
- `cycle_detection`: `O(V+E)` 時間、`O(V)` 補助領域と再帰スタック

## 境界・注意

- `shortest_path` では `e.to`, `e.cost`, `e.from` を参照します。
- `shortest_path` は Dijkstra 法なので負辺には使えません。距離加算が `T` の範囲を超えないようにしてください。
- 到達不能時は `path.empty()` で判定してください。返る `dist` は無限大ではなく値初期化された `T{}` です。
- `cycle_detection` では `e.to`, `e.id` を参照します。
- `cycle_detection` は有向・無向の両方に使えますが、辺 ID が各元辺で一意であることを仮定します。無向辺の両方向は同じ ID にしてください。
- 両関数とも `0<=s,t<V`（該当する引数について）が必要です。空グラフでは `cycle_detection` は空の組を返します。

## 使用例

```cpp
#include "graph/graph-utillity.hpp"

auto [path,dist]=shortest_path<long long>(g,s,t);
if(path.empty()){
    // unreachable
}
```

## 使用例

```cpp
auto [vs,es]=cycle_detection(g);
if(!vs.empty()){
    // cycle found
}
```
