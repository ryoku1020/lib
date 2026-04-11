---
title: Cograph Decomposition (補グラフの連結成分分解)
documentation_of: ../../graph/cographdecomposition.hpp
---

# Cograph Decomposition

与えられた頂点数 $N$ と「辺が存在しない頂点対（補グラフの辺）」のリストから、元のグラフの補グラフにおける連結成分を分解して返します。
つまり、与えられた非辺の集合を辺とみなしたグラフの連結成分を高速に求めるアルゴリズムです。

密グラフの連結成分分解などで、直接辺を管理するのではなく、欠損している辺（非辺）が少ない場合に有効です。

## cographdecomposition

```cpp
vvc<int> cographdecomposition(int n, vc<pair<int, int>> non_edge);
```

### 制約・引数
- `int n`: 頂点数 ($0 \le n$)
- `vc<pair<int, int>> non_edge`: 元のグラフに**存在しない辺**のリスト。各ペアは $(u, v)$ を表します。

### 戻り値
- 補グラフの各連結成分に含まれる頂点のリストの配列（`vvc<int>`）。
- 各 `vc<int>` がひとつの連結成分を表します。

### 計算量
- $O(N + M \log M)$ ($M$ は `non_edge` のサイズ)
内部で `FastSet` を用いてまだ訪問していない頂点を管理し、非辺を二分探索で判定しているため、高速に動作します。
