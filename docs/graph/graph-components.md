---
title: Graph Components (グラフの連結成分分解)
documentation_of: ../../graph/connectivity/graph-components.hpp
---

# Graph Components

無向グラフに対する二重辺連結成分分解(Two-edge-Connected Components)および二重頂点連結成分分解(Biconnected Components)を行うための構造体です。
グラフクラス `G` はLowlinkの計算（`is_bridge`, `ord`, `low` 等）がサポートされている必要があります。

## graph_components

```cpp
template<class G>
struct graph_components;
```

### コンストラクタ
- `graph_components(const G& g)`: 対象のグラフ `g` を受け取ります。グラフは無向グラフ（`G::directed() == false`）である必要があります。

### メソッド

#### `vc<int> edgec2() const`
二重辺連結成分分解 (Two-edge-Connected Components) を行います。
橋 (bridge) を取り除いたときに残る連結成分です。

- **戻り値**: サイズ $N$ (`g.size()`) の配列。各頂点 $i$ が属する成分のIDを返します。

#### `vc<int> vertexc2() const`
辺に対する二重頂点連結成分分解 (Biconnected Components) を行います。
関節点 (articulation point) を境界としてグラフを分解し、各辺がどの成分に属するかを分類します。

- **戻り値**: サイズ $M$ (`g.edge_size()`) の配列。各辺 $i$ が属する成分のIDを返します。孤立点は辺を持たないため、この配列には現れません。

#### `vvc<int> vertexc2vertex() const`
頂点に対する二重頂点連結成分分解 (Biconnected Components) を行います。
成分ごとに、その成分に含まれる頂点のリストを返します。関節点は複数の成分に属する可能性があります。また、孤立点はそれ自身のみを含むサイズ1の成分として扱われます。

- **戻り値**: `vvc<int>` (頂点リストの配列)。各要素が1つの二重頂点連結成分を構成する頂点の集合を表します。

## 境界・注意

- `G::directed()==false` を仮定します。
- `G` は `is_bridge(e)`, `ord(u)`, `low(u)` 相当の Lowlink 情報を提供している必要があります。
- `vertexc2()` は辺 ID ごとの成分 ID を返します。孤立点は辺を持たないため、この戻り値には現れません。

## 使用例

Lowlink 情報を持つ無向グラフ `g` に対して、橋を取り除いた成分 ID を得ます。

```cpp
graph_components components(g);

auto edge_component=components.edgec2();
auto biconn_vertices=components.vertexc2vertex();

for(auto& vs:biconn_vertices){
    // vs が 1 つの二重頂点連結成分
}
```
