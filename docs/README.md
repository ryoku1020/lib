---
title: Library Docs Index
---

# Library Docs

このディレクトリは競技プログラミング用ライブラリのドキュメント置き場です。
実装に対応する API ページには front matter の `documentation_of` が付いており、対応するソースファイルを追えるようになっています。移行案内など、特定の実装に対応しないページには付きません。

## 使い始め方

このライブラリは多くの実装が `template.hpp` に依存しています。
VSCode では `.vscode/settings.json` と `.clangd` で `template.hpp` を自動 include するようにしています。

```cpp
#include "ds/sequence/BIT.hpp"
#include "tree/base.hpp"
```

よくある使い方は次の 2 パターンです。

1. 問題に必要なファイルだけ include する
2. 手元の提出用テンプレートから必要な実装をコピペする

## ドキュメントの読み方

- `使用例` / `使い方`
  最小のサンプルコードです。まずここを見ると雰囲気を掴みやすいです。
- `メソッド`
  主要 API の意味と計算量をまとめています。
- `境界・注意`
  index の取り方、半開区間かどうか、事前 `build` が必要かどうか、などのハマりやすい点を書いています。
- `計算量`
  特記がなければ 1 回の操作に対する最悪計算量です。「ならし」「期待値」「構築」と書かれている場合はそれぞれ区別して読んでください。

各 API ページは、少なくともこの 3 点（使用例、境界・注意、計算量）を含めます。テンプレート引数に演算を渡すライブラリでは、その演算を `O(1)` とした計算量を記載しています。

## Chrome で見る

リポジトリのルートから次を実行すると、Markdown viewer を起動して Chrome で開きます。
数式は KaTeX、コードブロックは highlight.js で表示します。

```sh
python3 lib/docs/serve.py
```

手動で開く場合は次を使います。

```sh
python3 lib/docs/serve.py --no-open
```

## 代表的な入口

- 木: [tree / HLD](tree/base.md), [重心分解](tree/centroid.md), [DSU on tree](tree/dsu-on-tree.md), [輪郭クエリ](tree/contour.md), [全方位DP](ds/Reroot.md)
- 文字列: [Suffix Array / LCP](string/lcpsuf.md), [Z Algorithm](string/z-algorithm.md), [Aho-Corasick](string/aho-corasick.md), [manacher](string/manacher.md), [eer_tree](string/eer-tree.md)
- 数学: [mod_int](math/static-mod-int.md), [FPS](math/fps.md), [畳み込み](math/conv.md), [行列](math/mat.md), [分数](math/frac.md), [素数カウント](math/prime-counting.md), [Stern-Brocot木](math/stern-brocot-tree.md)
- データ構造: [bit](ds/BIT.md), [segtree](ds/segtree.md), [lazy_segtree](ds/lazy-segtree.md), [treap](ds/treap.md), [Wavelet行列](ds/wavelet-matrix.md), [sparse_table](ds/sparse-table.md)
- グラフ: [static_graph](graph/base.md), [最大流](graph/flow.md), [最小費用流](graph/min-cost-flow.md), [SCC](graph/scc.md), [2-SAT](graph/two-sat.md), [二部マッチング](graph/bipartite-match.md)

## 境界・注意: 存在しないファイルへの参照

以下は `documentation_of` が指すソースファイルが存在しません。

| ドキュメント | 状況 |
|------------|------|
| `docs/tree/hld.md` | `tree/hld.hpp` は存在しない。HLD は [`tree/base.hpp`](tree/base.md) の `tree` クラスに統合済み |
| `docs/ds/cht.md` | `ds/cht.hpp` は削除済み。用途別に li-chao-tree / dynamic-li-chao-tree / compressed-li-chao-tree を使う |
| `docs/other/commute-checker.md` | `other/commute-checker.hpp` は空ファイル |
| `docs/not_lib/tree/ahu.md` | `.not_lib/tree/ahu.hpp` は現在の `tree` API と非互換な試験コード。利用可能なライブラリには含めない |

## 使用例

木の LCA やパスクエリを調べたいときは、まず [tree](tree/base.md) を開きます。
ブラウザで数式付きで読みたい場合は viewer を起動します。

```sh
python3 lib/docs/serve.py --no-open
```

その後、表示された URL から `tree/base.md` を開きます。
