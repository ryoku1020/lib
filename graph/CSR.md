---
title: CSR Graph (Compressed Sparse Row 形式のグラフ)
documentation_of: ./CSR.cpp
---

# CSR Graph (Compressed Sparse Row 形式のグラフ)

グラフを `std::vector<std::vector<int>>` の代わりに、1次元配列に平坦化して保持するデータ構造です。
メモリの局所性が高まり、キャッシュヒット率が向上するため、グラフ探索の定数倍が高速になります。

## 使い方

```cpp
#include "graph/CSR.cpp"

// 頂点数 N で初期化
CSRgraph g(N);

// 辺の追加 (有向辺の場合。無向辺なら逆方向も追加する)
g.add_edge(u, v);
g.add_edge(v, u); // 無向グラフの場合

// すべての辺を追加したあとに build() を呼び出す
g.build();

// 頂点 u に隣接する頂点をイテレートする
for (int v : g[u]) {
    // 頂点 v に対する処理
}
```

## メソッド

### `CSRgraph(int n)`
頂点数 $n$ で初期化します。
- 計算量: $O(N)$

### `void add_edge(int u, int v)`
頂点 $u$ から 頂点 $v$ へ向かう有向辺を追加します。
- 制約: $0 \le u, v < N$ であり、まだ `build()` が呼び出されていないこと。
- 計算量: $O(1)$ amortized

### `void build()`
追加された辺をもとに、内部のCSR表現を構築します。
このメソッドを呼び出した後は `add_edge` で新たに辺を追加することはできません。
呼び出し時に一時的に持っていた辺の配列は削除され、メモリが解放されます。
- 計算量: $O(N + M)$ （$M$ は辺数）

### `RowView operator[](int u)`
頂点 $u$ から出る辺のリスト (隣接リスト) を返します。
戻り値はイテレータ `begin()` と `end()` を持つ軽量なビュー (RowView) であり、範囲 for 文 (`for(int v : g[u])`) に対応しています。
- 制約: `build()` 呼び出し済みであること。$0 \le u < N$。
- 計算量: 取得は $O(1)$。
