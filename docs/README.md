---
title: ライブラリ索引 | 用途・API 名
---

# ライブラリ索引

競技中に用途からページを選び、API・区間の端点・制約を確認するための索引です。実装は [`lib`](../) の C++20 ヘッダにあります。各ページの `documentation_of` が対応する実装ファイルです。

## まず選ぶ

| やりたいこと | ページ | API 名・検索語 |
|---|---|---|
| 点更新・区間集約 | [セグメント木](ds/segtree.md)、[遅延セグメント木](ds/lazy-segtree.md) | `segtree`, `lazy_segtree`, `query`, `prod` |
| 区間更新・一点取得 | [dual segment tree](ds/dual-segtree.md) | `dual_segtree` |
| 区間代入・区間集約 | [assign segment tree](ds/assign-segtree.md) | `assign_segtree` |
| 巨大な座標範囲 | [dynamic segment tree](ds/dynamic-segtree.md)、[dynamic lazy segment tree](ds/dynamic-lazy-segtree.md) | `dynamic_segtree`, `dynamic_lazy_segtree` |
| 静的 RMQ / 変化しない区間集約 | [sparse table](ds/sparse-table.md) | `sparse_table` |
| 1 点加算・prefix / 区間和 | [Fenwick tree](ds/bit.md) | `binary_indexed_tree`, `bit` |
| XOR 最小値・k 番目 | [binary trie](ds/binary-trie.md) | `binary_trie`, `xor`, `kth` |
| 木の LCA・パス・部分木 | [tree / HLD](tree/base.md) | `tree`, `lca`, `query`, `in`, `out` |
| 強連結成分 / 2-SAT | [SCC](graph/scc.md)、[2-SAT](graph/two-sat.md) | `scc`, `two_sat` |
| 最大流 / 最小費用流 | [最大流](graph/flow.md)、[最小費用流](graph/min-cost-flow.md) | `flow`, `min_cost_flow` |
| 多項式積・FPS | [畳み込み](math/conv.md)、[形式的冪級数](math/fps.md) | `convolution`, `fps` |
| 文字列一致・区間ハッシュ | [KMP / Z](string/z-algorithm.md)、[Rolling Hash](string/rolling-hash.md) | `z_algorithm`, `rolling_hash` |

## 全ページ

### データ構造 (`ds/`)

| 用途 | ページ |
|---|---|
| セグメント木 | [segment tree / `segtree`](ds/segtree.md) · [lazy segment tree / `lazy_segtree`](ds/lazy-segtree.md) · [assign segment tree / `assign_segtree`](ds/assign-segtree.md) · [dual segment tree / `dual_segtree`](ds/dual-segtree.md) · [dynamic segment tree / `dynamic_segtree`](ds/dynamic-segtree.md) · [dynamic lazy segment tree / `dynamic_lazy_segtree`](ds/dynamic-lazy-segtree.md) · [persistent lazy segment tree](ds/persistent-lazy-segtree.md) |
| 区間集約・列 | [Fenwick tree / `binary_indexed_tree`](ds/bit.md) · [sparse table](ds/sparse-table.md) · [SWAG](ds/swag.md) · [Mo's algorithm](ds/mo.md) · [wavelet matrix](ds/wavelet-matrix.md) · [static mode](ds/static-mode.md) · [bit vector](ds/bit-vector.md) |
| 集合・木構造 | [Union-Find](ds/uf.md) · [potential Union-Find](ds/pot-uf.md) · [rollback Union-Find](ds/undo-uf.md) · [persistent Union-Find](ds/persistent-uf.md) · [range Union-Find](ds/range-uf.md) · [binary trie](ds/binary-trie.md) · [trie](ds/trie.md) · [treap](ds/treap.md) · [set treap](ds/setreap.md) · [fast set](ds/fastset.md) · [hash map / range set](ds/ordered-extra.md) |
| 直線・最適化 | [Li Chao tree 選択](ds/cht.md) · [Li Chao tree](ds/li-chao-tree.md) · [dynamic Li Chao tree](ds/dynamic-li-chao-tree.md) · [compressed Li Chao tree](ds/compressed-li-chao-tree.md) · [CHT](ds/cht.md) · [slope trick](ds/slope-trick.md) |
| その他 | [座標圧縮](ds/compress.md) · [persistent array](ds/persistent-array.md) · [double priority queue](ds/double-priority-queue.md) · [node pool](ds/node-pool.md) · [range data structure 追加実装](ds/range-extra.md) · [monoid / action 定義](ds/algebra.md) · [famous helper 移行](ds/famous.md) · [Hash Map / range set](ds/ordered-extra.md) · [rectangle union](ds/rectangle-union.md) · [rolling hash 用 hash 型](ds/hash.md) |

### グラフ (`graph/`)

[グラフ基本型・入力](graph/base.md) · [旧 CSR 型からの移行](graph/CSR.md) · [SCC](graph/scc.md) · [増分 SCC](graph/incremental-scc.md) · [2-SAT](graph/two-sat.md) · [連結成分](graph/graph-components.md) · [グラフ補助関数](graph/graph-utillity.md) · [二部マッチング](graph/bipartite-match.md) · [最大流](graph/flow.md) · [最小費用流](graph/min-cost-flow.md) · [k 番目最短 walk](graph/kth-shortest-path.md) · [クリーク列挙](graph/enumerate-clique.md) · [三角形列挙](graph/enumerate-triangle.md) · [cograph 分解](graph/cograph-decomposition.md) · [グラフ API 追加実装](graph/advanced.md)

### 数学・多項式 (`math/`, `poly/`)

[静的 modint](math/static-mod-int.md) · [動的 modint](math/dynamic-mod-int.md) · [mod 2^61−1](math/mod261.md) · [Barrett reduction](math/barrett.md) · [行列](math/mat.md) · [畳み込み](math/conv.md) · [AND 畳み込み](math/and-convolution.md) · [XOR 畳み込み](math/xor-convolution.md) · [FPS](math/fps.md) · [Bostan–Mori](math/bostan-mori.md) · [二項係数・整数論](math/advanced.md) · [篩・行列・数値型](math/arithmetic.md) · [多項式 API](poly/README.md)

### 文字列・木・幾何

[Aho–Corasick](string/aho-corasick.md) · [回文木](string/eer-tree.md) · [suffix array / LCP](string/lcpsuf.md) · [Manacher](string/manacher.md) · [Rolling Hash](string/rolling-hash.md) · [Z algorithm](string/z-algorithm.md) · [run 列挙](string/run-enumarate.md) · [KMP・suffix automaton・wildcard match](string/advanced.md) · [木の基本・HLD](tree/base.md) · [HLD 移行案内](tree/HLD.md) · [centroid decomposition](tree/centroid.md) · [contour query](tree/contour.md) · [DSU on tree](tree/dsu-on-tree.md) · [木上 Mo](tree/mo.md) · [木 API 追加実装](tree/advanced.md) · [2D 点](geometry/point.md) · [幾何 API 追加実装](geometry/advanced.md)

### その他

[高速入出力](fast-io.md) · [template.hpp](template.md) · [Monge 行列](monge.md) · [commute checker](other/commute-checker.md) · [開発・検証用の生成器](other/generator.md)

## 表記

- 添字は特記がなければ 0-indexed、区間は `[l,r)` です。閉区間や包含範囲を使う API はページ内に明記しています。
- 計算量はコードの実装に基づきます。`ならし`・`期待`・前処理後などの条件も併記します。
- include は通常 `#include "ds/segment_tree/segtree.hpp"` のように `lib/` からの相対パスで示します。共通型・標準ヘッダのため [`template.hpp`](template.md) を使う例もあります。
