---
title: Graph Utility
documentation_of: ../../graph/graph_utillity.hpp
---

# Graph Utility

グラフアルゴリズムにおける一般的なユーティリティ関数を提供するヘッダです。ダイクストラ法による単一始点・単一終点の最短路や、DFSを用いた閉路検出などが含まれます。

## shortest_path

```cpp
template<class T, class Graph>
pair<vc<int>, T> shortest_path(const Graph& g, int s, int t);
```
ダイクストラ法を用いて、頂点 $s$ から頂点 $t$ への最短経路およびそのコストを求めます。

### 制約・引数
- `class T`: 辺の重みや距離の型 (例: `int`, `long long`)
- `const Graph& g`: グラフ。隣接リスト表現 (`g[v]` で頂点 `v` から出る辺 `e` を走査できること。`e` は `to`, `cost` 等のメンバを持つ必要があります)
- `int s`: 始点
- `int t`: 終点

### 戻り値
- `pair<vc<int>, T>`:
  - `.first` (`vc<int>`): $s$ から $t$ までの最短経路上の頂点列 (例: `[s, v1, v2, ..., t]`)。経路が存在しない場合は空の `vc<int>` が返ります。
  - `.second` (`T`): 最短経路のコスト。経路が存在しない場合は不定です(実際はデフォルト初期化値が返ります)。

### 計算量
- $O((V + E) \log V)$ (優先度付きキューを使用)

## cycle_detection

```cpp
template<class Graph>
pair<vc<int>, vc<int>> cycle_detection(const Graph& g);
```
深さ優先探索(DFS)を用いて、グラフ内の閉路を一つ検出します。有向・無向問わず動作しますが、直前に通った辺を逆走しない（`e.id == eid`）判定があるため、無向グラフの場合は長さ2の単純な往復を閉路とみなしません。

### 制約・引数
- `const Graph& g`: グラフ。隣接リスト表現 (`g[v]` で頂点 `v` から出る辺 `e` を走査できること。`e` は `to`, `id` 等のメンバを持つ必要があります)

### 戻り値
- `pair<vc<int>, vc<int>>`:
  - `.first` (`vc<int>`): 閉路を構成する頂点の列
  - `.second` (`vc<int>`): 閉路を構成する辺のIDの列
  - 閉路が存在しない場合は、両方とも空の `vc<int>` が返ります。

### 計算量
- $O(V + E)$
