---
title: Tree (HLD / 木の基本操作)
documentation_of: ../../tree/base.hpp
---

# Tree

木に対する基本的なクエリ処理と、Heavy-Light Decomposition (HLD) によるパス・部分木クエリのための構造体です。
`static_graph<1>` を用いており、構築後は高速にLCAや頂点間の距離、パス上のクエリを処理できます。

## `Tree`

### コンストラクタ
- `Tree(int n, Graph& g)`: 頂点数 $n$ のグラフ `g` を用いて木のインスタンスを生成します。グラフは有向として扱われますが、`add_edge` 内で双方向に辺を張るため実質無向グラフになります。

### メソッド

- `void add_edge(int a, int b)`
  頂点 $a, b$ 間に無向辺を追加します。

- `void input<int subtract>()`
  標準入力から $N-1$ 本の辺（形式: `u v`）を読み込みます。`subtract` を指定することで、例えば 1-indexed の入力を 0-indexed に変換して読み込むことができます。

- `void build(int root = 0) const`
  頂点 `root` を根として、Heavy-Light Decomposition (HLD) の前計算を行います。各頂点の部分木サイズ、深さ、親、HLD上での行きがけ順 (`in`), 帰りがけ順 (`out`), Heavy Path の先頭 (`head`) などを計算します。
  ※ LCAや距離などのクエリメソッドを呼ぶと、内部で自動的に呼び出されます。
  計算量: $O(N)$

- `int lca(int a, int b) const`
  頂点 $a$ と $b$ の最小共通祖先 (Lowest Common Ancestor) を返します。
  計算量: $O(\log N)$

- `int dist(int a, int b) const`
  頂点 $a$ と $b$ の間の距離（辺数）を返します。
  計算量: $O(\log N)$

- `int jumpup(int a, int k) const`
  頂点 $a$ から根に向かって $k$ 回移動したときの頂点を返します。範囲外の場合は `-1` を返します。
  計算量: $O(\log N)$

- `int jump(int s, int t, int k) const`
  頂点 $s$ から頂点 $t$ に向かって $k$ 回移動したときの頂点を返します。
  計算量: $O(\log N)$

- `vc<pair<int, int>> Query(int s, int t) const`
  パス $s \to t$ に対応する、HLD上で連続する区間 $[l, r]$ のリストを返します。
  セグメント木などでパスに対するクエリ（遅延評価など）を行う際に使用します。
  計算量: $O(\log N)$

- `pair<int, int> get_diameter() const`
  木の直径の端点となる頂点のペアを返します。
  計算量: $O(N)$

### メンバ変数 (一部)
- `in`, `out`: HLDの行きがけ・帰りがけ順のタイムスタンプ。部分木クエリは区間 `[in[v], out[v])` で表現されます。
- `depth`: 根からの深さ。
- `size_`: 部分木の頂点数。
- `par`: 親頂点。根の親は `-1` になる想定です（この実装では未定義に注意）。
