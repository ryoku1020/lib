---
title: IncrementalScc
documentation_of: ../../graph/incremental-scc.hpp
---

# IncrementalScc

有向辺を時系列に追加していったときの SCC マージをオフラインで処理する補助構造です。
かなり特殊用途寄りです。

## コンストラクタ

### `IncrementalScc(int n = 0)`

頂点数 `n` で初期化します。

## メソッド

### `void inc.push(int a, int b)`

時刻順に辺 `a->b` を追加します。

### `vc<graph::edge> inc.work()`

内部処理を行い、マージ情報を返します。
返る `edge` の `id` にはそのマージが起きた時刻 index が入ります。

## 注意

- 一般用途の SCC ではなく、増加列に対する特殊なオフライン処理です。
- 詳しい利用側はこのリポジトリ内の実利用コードに合わせて読むのが安全です。
