---
title: static_graph
documentation_of: ../../graph/base.hpp
---

# static_graph

CSR 形式をベースにしたグラフ構造です。
有向・無向、重み付き・重みなしの両方を扱えます。

## 型

### `unweighted`

重みなしグラフ用のダミー重み型です。

### `edge<T>`

辺は次のメンバを持ちます。

- `from`
- `to`
- `id`
- `cost`

## クラス

### `static_graph<is_directed, T>`

- `is_directed=true`
  有向グラフ
- `is_directed=false`
  無向グラフ
- `T`
  辺重み型です。省略時は `unweighted`

## コンストラクタ

### `static_graph(int n)`

頂点数 `n` のグラフを作ります。

### `static_graph(int n, int m)`

頂点数 `n`、辺数 `m` を想定して reserve 付きで作ります。
`m` は容量予約にだけ使われ、追加辺数が `m` に達しても `build()` は走りません。

## メソッド

### `void g.add_edge(int a, int b, cost_t cost = 1, int id = -1)`

辺を追加します。
`id==-1` なら追加順の id が自動で振られます。

- 制約: `0<=a,b<n`
- 計算量: amortized `O(1)`

### `void g.add_edge(const edge& e)`

辺オブジェクトを直接追加します。

- 制約: `0<=e.from,e.to<n`
- 計算量: amortized `O(1)`

### `void g.resize(int size)`

未構築のグラフの頂点数を `size` まで増やします。縮小はできません。

- 制約: 現在の頂点数以下へ縮小しないこと、CSR 構築前であること
- 計算量: `O(size-n)`

### `template<int substract=0> void g.input(int m)`

`m` 本の辺 `a b` を入力し、両端から `substract` を引いて追加した後に `build()` します。

- 計算量: `O(n+m)`

### `void g.build() const`

隣接リストの CSR 構築を行います。
通常は `g[u]` を呼んだとき自動で行われます。

- 計算量: `O(n+m)`

### `void g.buildinv() const`

有向グラフで逆辺 CSR を構築します。
通常は `inv(u)` を呼んだとき自動で行われます。

- 計算量: `O(n+m)`

現行実装では完了時に `inv_built=true` を設定していないため、`buildinv()`, `inv(u)`, `in_deg(u)` を呼ぶたびに逆辺 CSR を再構築します。

### `auto g[u]`

頂点 `u` から出る辺の列を返します。

```cpp
for(auto&e:g[u]){
    int to=e.to;
}
```

- 計算量: 初回は `O(n+m)`、構築後の view 取得は `O(1)`、走査は `O(out_deg(u))`

### `auto g.inv(u)`

頂点 `u` に入る辺の列を返します。
無向グラフでは `g[u]` と同じです。

- 計算量: 現行実装では view 取得ごとに `O(n+m)`、走査はさらに `O(in_deg(u))`

### `const vc<edge>& g.all_edges() const`

追加した元辺列を返します。

### `int g.edge_size() const`

元辺数を返します。

### `edge g.get_edge(int id) const`

追加順で `id` 番目に格納された元辺を返します。引数は辺オブジェクトの `edge.id` を検索するものではありません。

### `int g.out_deg(int u) const`
### `int g.in_deg(int u) const`
### `int g.deg(int u) const`

出次数、入次数、次数を返します。

### `int g.size() const`

頂点数を返します。

### `vvc<F> g.adj() const`

隣接行列風の 2 次元配列を返します。

呼び出し時は重みの格納型を明示して `g.template adj<F>()` とします。

- 計算量: `O(n^2+m)` 時間、`O(n^2)` 領域

### `void g.clear()`

保持している辺と CSR を消します。

### `void g.sort(int i, F f)`

頂点 `i` の隣接辺を比較関数 `f` でソートします。

- 計算量: CSR 未構築ならその `O(n+m)` に加え、`O(out_deg(i) log out_deg(i))`

`sort_inv`, `extract`, `reorder` は現行の `graph/base.hpp` にはありません。

## 計算量まとめ

- 構築: `O(n+m)` 時間、`O(n+m)` 領域（無向グラフの CSR は各元辺を 2 本保持）
- `add_edge`: amortized `O(1)`
- 構築後の `g[u]`, `out_deg`, `deg`, `size`, `edge_size`, `get_edge`: view や値の取得は `O(1)`
- `all_edges`: `O(1)` で参照を返し、全走査は `O(m)`
- 逆辺関連: 上述のキャッシュフラグの都合で、現行実装は呼び出しごとに `O(n+m)`

## 境界・注意

- 頂点番号は 0-indexed です。
- 無向グラフでは内部 CSR 上には両向きの辺が入りますが、`all_edges()` は元に追加した辺だけを返します。
- `g[u]` などで通常 CSR を一度構築すると、それ以後の `add_edge` と `resize` は `assert` に失敗します。すべての辺を先に追加してください。
- `id==-1` の自動 ID は追加時点の格納位置と一致します。明示 ID は重複や範囲を検査しないため、ID を配列添字として使うアルゴリズムでは `0,1,...,m-1` の連番にしてください。
- 無向自己ループは CSR に同じ ID で 2 本格納されます。

## 使用例 1: 重みなし有向グラフ

```cpp
#include "graph/base.hpp"

static_graph<1> g(n);
g.add_edge(u,v);
g.add_edge(v,w);

for(auto&e:g[u]){
    // e.to
}
```

## 使用例 2: 重み付き無向グラフ

```cpp
static_graph<0,long long> g(n);
g.add_edge(u,v,cost);

for(auto&e:g[u]){
    long long c=e.cost;
}
```
