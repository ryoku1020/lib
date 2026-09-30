---
title: Graph Utility | 移行案内
documentation_of: ../../graph/base.hpp
keywords: Graph Utility, shortest_path, cycle_detection, graph utility
---

# Graph Utility の移行案内

旧 `graph/graph-utillity.hpp` はありません。現在の機能は個別ヘッダに分かれています。

- 距離だけを求める: [`dijkstra`](advanced.md#経路) (`graph/path/dijkstra.hpp`)
- 距離と頂点・辺列を復元: [`shortest_path`](advanced.md#経路) (`graph/path/shortest-path.hpp`)
- 閉路を検出: [`cycle_detection`](advanced.md#経路) (`graph/path/cycle-detection.hpp`)
- グラフ型: [`static_graph`](base.md)

`shortest_path<T>(g,s,t)` の実装上の返却予定型は `{{vertices,edges},distance}` ですが、内部でコンパイル不能な `dijkstra<T>(g,s)` 呼び出しを行うため現状そのままでは利用できません。Dijkstra は `dijkstra<T>(g, vc<int>{s})` の形で使えます。詳しくは [追加経路 API](advanced.md#経路) を確認してください。
