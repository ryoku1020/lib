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

空集合を除くすべてのクリークをそれぞれ 1 回列挙します。最大クリークだけを列挙する関数ではありません。

## 計算量

頂点を除去した時点での隣接生存頂点数を $d_i$ とすると、実装は `2^{d_i}` 個の部分集合を調べ、各候補の全頂点対を検査します。そのためコールバックの時間を除いて

`O(N^3 + sum_i 2^{d_i} (d_i+1)^2)`

時間、`O(N^2)` 領域です。`N^3` は、各除去段階で全生存頂点の次数を隣接行列から数え直す分です。完全グラフでの最悪計算量は `O(N^2 2^N)` です。`O(3^{N/3})` は最大クリーク列挙に現れる評価であり、この全クリーク列挙実装には当てはまりません。

## 境界・注意

- 無向グラフのみ対応しています（有向グラフを渡すと `static_assert` で失敗）。
- 単純グラフを前提とします。自己ループは入れないでください。
- 全クリーク列挙のため、密グラフでは指数的に遅くなります。
- 部分集合に符号付き `int` のビットマスクを使うため、処理中の `d_i+1` は 30 以下に抑える必要があります。
- `g.template adj<int>()` で `N*N` の隣接行列を作るため、重みは `int` に変換できる必要があります。
- 最大クリークのみが必要で頂点数が大きい場合は、専用アルゴリズムを検討してください。

## 使用例

```cpp
#include "graph/enumerate-clique.hpp"

// 無向グラフを構築
static_graph<0> g(3);
g.add_edge(0,1);
g.add_edge(1,2);
g.add_edge(0,2);

int max_clique = 0;
enumerate_clique(g, [&](const vc<int>& cl){
    chmax(max_clique, (int)cl.size());
});
// max_clique == 3
```
