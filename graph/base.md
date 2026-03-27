---
title: Static Graph (静的グラフのベースクラス)
documentation_of: ./base.cpp
---

# Static Graph (静的グラフのベースクラス)

競技プログラミング向けの汎用グラフ表現クラスです。
CSR (Compressed Sparse Row) 形式をベースにしており、有向・無向グラフ、重み付き・重みなしグラフをサポートします。
グラフアルゴリズム (最短経路や閉路検出) のベースとして使用されます。

## 使い方

```cpp
#include "graph/base.cpp"

// 頂点数 N の重みなし有向グラフ
static_graph<true, Unweighted> g(N);

// 頂点数 N の重み付き無向グラフ (重みの型は long long)
static_graph<false, long long> wg(N);

// 辺の追加
g.add_edge(u, v);
wg.add_edge(u, v, cost);

// 頂点 u の隣接リストの走査
// operator[] は内部で自動的に build() を呼び出します
for (auto& e : wg[u]) {
    int to = e.to;
    long long cost = e.cost;
    int id = e.id; // 追加された順の 0-indexed な ID
}

// 逆辺の走査 (有向グラフの場合)
for (auto& e : g.inv(v)) {
    // v へ向かってくる辺
}
```

## メソッド

### `static_graph(int n)`
頂点数 $n$ のグラフを初期化します。
- 計算量: $O(N)$

### `void add_edge(int a, int b, T cost = 1)`
頂点 $a$ から $b$ への辺 (重み `cost`) を追加します。
無向グラフの場合は、逆方向の辺も内部で自動的に処理されます。
- 制約: $0 \le a, b < n$
- 計算量: $O(1)$ amortized

### `void build() const` / `void build_inv() const`
内部の CSR 配列を構築します。通常は `operator[]` や `inv()` を呼び出した際に自動的に実行されるため、明示的に呼ぶ必要はありません。
- 計算量: $O(N + M)$

### `auto operator[](int u)`
頂点 $u$ から出る辺のリストへのイテレータブルな View (span) を返します。
- 制約: $0 \le u < n$
- 計算量: 構築済みなら $O(1)$

### `int out_deg(int u) const` / `int in_deg(int u) const`
頂点 $u$ の出次数 / 入次数を返します。
- 計算量: $O(1)$ (構築完了後)

## 付属アルゴリズム

### `pair<vector<int>, T> shortest_path(const Graph& g, int s, int t)`
Dijkstra法を用いて、頂点 $s$ から $t$ への最短経路を求めます。
戻り値は `(パスの頂点列, 最短距離)` のペアです。到達不可能な場合は空のリストと型の最大値を返します。
- 制約: 辺の重みは非負であること。
- 計算量: $O((N + M) \log M)$

### `pair<vector<int>, vector<int>> cycle_detection(const Graph& g)`
グラフ内の閉路を一つ検出します。
戻り値は `(閉路を構成する頂点列, 閉路を構成する辺のID列)` のペアです。閉路が存在しない場合は空のリストを返します。
- 計算量: $O(N + M)$
