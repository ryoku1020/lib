---
title: Cograph Decomposition (非辺リストによる連結成分分解)
documentation_of: ../../graph/coloring/cograph-decomposition.hpp
---

# Cograph Decomposition

与えられた頂点数 $N$ と「辺が存在しない頂点対（非辺）」のリストから、元の密グラフの連結成分を分解して返します。
つまり、全頂点対のうち `non_edge` に含まれないものを辺とみなしたグラフの連結成分を高速に求めるアルゴリズムです。

密グラフの連結成分分解などで、直接辺を管理するのではなく、欠損している辺（非辺）が少ない場合に有効です。

## cograph-decomposition

```cpp
vvc<int> cographdecomposition(int n, vc<pair<int, int>> non_edge);
```

### 制約・引数
- `int n`: 頂点数 ($0 \le n$)
- `vc<pair<int, int>> non_edge`: 元のグラフに**存在しない辺**のリスト。各ペアは $(u, v)$ を表します。

### 戻り値
- `non_edge` に含まれない頂点対を辺とみなしたグラフの各連結成分に含まれる頂点のリストの配列（`vvc<int>`）。
- 各 `vc<int>` がひとつの連結成分を表します。

### 計算量
- $O(N + M \log M)$ ($M$ は `non_edge` のサイズ)
内部で `fast_set` を用いてまだ訪問していない頂点を管理し、非辺を二分探索で判定しているため、高速に動作します。

## 境界・注意

- `non_edge` は無向グラフの非辺として扱われ、内部で両向きに登録されます。
- 自己ループは不要です。実装内で各頂点自身は非辺扱いに追加されます。
- 疎グラフの通常の連結成分分解には向きません。辺ではなく非辺が少ない密グラフ向けです。

## 使用例

完全グラフから一部の辺だけが欠けているグラフの連結成分を求めます。

```cpp
#include "graph/coloring/cograph-decomposition.hpp"

int n=5;
vc<pair<int,int>> non_edge={
    {0,1},
    {3,4},
};

auto comps=cographdecomposition(n,non_edge);
for(auto& vs:comps){
    // vs が 1 つの連結成分
}
```
