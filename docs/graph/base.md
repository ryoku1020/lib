---
title: StaticGraph
documentation_of: ../../graph/base.hpp
---

# StaticGraph

CSR 形式をベースにしたグラフ構造です。
有向・無向、重み付き・重みなしの両方を扱えます。

## 型

### `Unweighted`

重みなしグラフ用のダミー重み型です。

### `Edge<T>`

辺は次のメンバを持ちます。

- `from`
- `to`
- `id`
- `cost`

## クラス

### `StaticGraph<is_directed, T>`

- `is_directed=true`
  有向グラフ
- `is_directed=false`
  無向グラフ
- `T`
  辺重み型です。省略時は `Unweighted`

## コンストラクタ

### `StaticGraph(int n)`

頂点数 `n` のグラフを作ります。

### `StaticGraph(int n, int m)`

頂点数 `n`、辺数 `m` を想定して reserve 付きで作ります。
追加辺数がちょうど `m` に達すると内部で `build()` が走ります。

## メソッド

### `void g.add_edge(int a, int b, cost_t cost = 1, int id = -1)`

辺を追加します。
`id==-1` なら追加順の id が自動で振られます。

- 制約: `0<=a,b<n`
- 計算量: amortized `O(1)`

### `void g.add_edge(const Edge& e)`

辺オブジェクトを直接追加します。

### `void g.build() const`

隣接リストの CSR 構築を行います。
通常は `g[u]` を呼んだとき自動で行われます。

- 計算量: `O(n+m)`

### `void g.build_inv() const`

有向グラフで逆辺 CSR を構築します。
通常は `inv(u)` を呼んだとき自動で行われます。

- 計算量: `O(n+m)`

### `auto g[u]`

頂点 `u` から出る辺の列を返します。

```cpp
for(auto&e:g[u]){
    int to=e.to;
}
```

### `auto g.inv(u)`

頂点 `u` に入る辺の列を返します。
無向グラフでは `g[u]` と同じです。

### `const vc<Edge>& g.all_edges() const`

追加した元辺列を返します。

### `int g.edge_size() const`

元辺数を返します。

### `Edge g.get_edge(int id) const`

id 番目の元辺を返します。

### `int g.out_deg(int u) const`
### `int g.in_deg(int u) const`
### `int g.deg(int u) const`

出次数、入次数、次数を返します。

### `int g.size() const`

頂点数を返します。

### `vvc<F> g.adj() const`

隣接行列風の 2 次元配列を返します。

### `void g.clear()`

保持している辺と CSR を消します。

### `void g.sort(int i, F f)`
### `void g.sort_inv(int i, F f)`

頂点 `i` の隣接辺を比較関数 `f` でソートします。

### `auto g.extract(F f) const`

元辺のうち `f(e)` を満たすものだけを抜き出したグラフを返します。

### `auto g.reorder(F f) const`

各辺 `e` について、`f(e)` が偽なら向きを反転した有向グラフを返します。

## 使用例 1: 重みなし有向グラフ

```cpp
#include "graph/base.hpp"

StaticGraph<1> g(n);
g.add_edge(u,v);
g.add_edge(v,w);

for(auto&e:g[u]){
    // e.to
}
```

## 使用例 2: 重み付き無向グラフ

```cpp
StaticGraph<0,long long> g(n);
g.add_edge(u,v,cost);

for(auto&e:g[u]){
    long long c=e.cost;
}
```

## 注意

- 頂点番号は 0-indexed です。
- 無向グラフでは内部 CSR 上には両向きの辺が入りますが、`all_edges()` は元に追加した辺だけを返します。
