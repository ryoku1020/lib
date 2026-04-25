---
title: Library Docs Index
---

# Library Docs

このディレクトリは競技プログラミング用ライブラリのドキュメント置き場です。
各 `.md` には `documentation_of` が付いており、対応する実装ファイルを追えるようになっています。

## 使い始め方

このライブラリは多くの実装が `template.hpp` に依存しています。
単体で使うときは、そのファイル自身が `template.hpp` を include しているかをまず確認してください。

```cpp
#include "template.hpp"
#include "ds/BIT.hpp"
#include "tree/base.hpp"
```

よくある使い方は次の 2 パターンです。

1. 問題に必要なファイルだけ include する
2. 手元の提出用テンプレートから必要な実装をコピペする

## ドキュメントの読み方

- `使い方`
  最小のサンプルコードです。まずここを見ると雰囲気を掴みやすいです。
- `メソッド`
  主要 API の意味と計算量をまとめています。
- `注意`
  index の取り方、半開区間かどうか、事前 `build` が必要かどうか、などのハマりやすい点を書いています。

## 代表的な入口

- 木: [docs/tree/base.md](/Users/ryoku_/Desktop/cp/lib/docs/tree/base.md), [docs/tree/dsu-on-tree.md](/Users/ryoku_/Desktop/cp/lib/docs/tree/dsu-on-tree.md), [docs/tree/centroid.md](/Users/ryoku_/Desktop/cp/lib/docs/tree/centroid.md)
- 文字列: [docs/string/lcpsuf.md](/Users/ryoku_/Desktop/cp/lib/docs/string/lcpsuf.md), [docs/string/z-algorithm.md](/Users/ryoku_/Desktop/cp/lib/docs/string/z-algorithm.md), [docs/string/aho-corasick.md](/Users/ryoku_/Desktop/cp/lib/docs/string/aho-corasick.md)
- 数学: [docs/math/mod.md](/Users/ryoku_/Desktop/cp/lib/docs/math/mod.md), [docs/math/conv.md](/Users/ryoku_/Desktop/cp/lib/docs/math/conv.md), [docs/math/frac.md](/Users/ryoku_/Desktop/cp/lib/docs/math/frac.md)
- データ構造: [docs/ds/BIT.md](/Users/ryoku_/Desktop/cp/lib/docs/ds/BIT.md), [docs/ds/seg.md](/Users/ryoku_/Desktop/cp/lib/docs/ds/seg.md), [docs/ds/lazy_seg.md](/Users/ryoku_/Desktop/cp/lib/docs/ds/lazy_seg.md)
- グラフ: [docs/graph/base.md](/Users/ryoku_/Desktop/cp/lib/docs/graph/base.md), [docs/graph/flow.md](/Users/ryoku_/Desktop/cp/lib/docs/graph/flow.md), [docs/graph/min-cost-flow.md](/Users/ryoku_/Desktop/cp/lib/docs/graph/min-cost-flow.md)

## 今回追加した主なページ

- tree: centroid decomposition / countour_add / DSU on Tree
- string: Z algorithm / Manacher / Aho-Corasick / EerTree / Run Enumerate
- math: Frac / kth_root / prime_counting / enumerate_floor / GoldenSearch
- graph: MinCostFlow
