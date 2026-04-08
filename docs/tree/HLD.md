---
title: Heavy-Light Decomposition (HL分解)
documentation_of: ../../tree/HLD.hpp
---

# Heavy-Light Decomposition (HL分解)

木をパス (Heavy-edge) の集合に分解し、パス上の頂点・辺のクエリを列のクエリに帰着させます。
木の任意のパスは $O(\log N)$ 個の区間に分割されます。
LCAや2頂点間の距離、パス上の頂点の取得などもサポートしています。

## 使い方

```cpp
#include "tree/HLD.cpp"

// 頂点数 N で初期化
HLD hld(N);

// 無向辺を追加
hld.ae(u, v);

// 構築 (根を 0 として分解を行う)
hld.build();

// u と v の Lowest Common Ancestor
int lca = hld.lca(u, v);

// 頂点 s から t へのパス上で s から距離 k の頂点を取得
int v = hld.jump(s, t, k);

// s から t へのパスを区間に分解して取得
// {l, r} のリストが s 側から順に返る (l > r になる区間は、頂点を逆方向に進むことを意味する)
auto path = hld.Query(s, t);
```

## メソッド

### `HLD(int n)`
頂点数 $n$ の森として初期化します。内部で `CSRgraph` を用いています。
- 計算量: $O(N)$

### `void ae(int a, int b)`
頂点 $a$ と $b$ の間に無向辺を追加します。
- 計算量: $O(1)$ amortized

### `void build()`
追加された辺をもとに、頂点 0 を根とした根付き木として HL分解 を構築します。
DFS によって各頂点の `in`, `out`（オイラーツアーの行きがけ・帰りがけの時刻）、`head`（属する Heavy-path の最も浅い頂点）、`size`（部分木のサイズ）などを計算します。
- 制約: 辺がすべて追加された後に呼び出すこと。
- 計算量: $O(N)$

### `int lca(int a, int b)`
頂点 $a$ と $b$ の最小共通祖先 (LCA: Lowest Common Ancestor) を返します。
- 制約: 0-indexed で $0 \le a, b < N$
- 計算量: $O(\log N)$

### `int dist(int a, int b)`
頂点 $a$ と $b$ のパス上の辺の数 (距離) を返します。
- 計算量: $O(\log N)$

### `int jumpup(int a, int k)`
頂点 $a$ の $k$ 個上の祖先を返します。存在しない場合は `-1` を返します。
- 計算量: $O(\log N)$

### `int jump(int s, int t, int k)`
頂点 $s$ から $t$ へ向かうパス上で、$s$ から距離 $k$ にある頂点を返します。
そのような頂点が存在しない (距離が $k$ 未満) 場合は `-1` を返します。
- 計算量: $O(\log N)$

### `std::vector<std::pair<int, int>> Query(int s, int t)`
頂点 $s$ から $t$ へのパスを、HL分解の `in` 配列 (オイラーツアー順) における $O(\log N)$ 個の閉区間 $[l, r]$ の列として返します。
セグメント木などのデータ構造にクエリを投げる際に用います。
返される区間 $\{u, v\}$ において、$u > v$ となっている場合、セグメント木等において「右から左へ」評価する必要があることに注意してください。
- 計算量: $O(\log N)$
