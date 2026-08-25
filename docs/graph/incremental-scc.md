---
title: incremental_scc
documentation_of: ../../graph/connectivity/incremental-scc.hpp
---

# incremental_scc

有向辺を時系列に追加していったときの SCC マージをオフラインで処理する補助構造です。
かなり特殊用途寄りです。

## コンストラクタ

### `incremental_scc(int n = 0)`

頂点数 `n` で初期化します。

## メソッド

### `void inc.push(int a, int b)`

時刻順に辺 `a->b` を追加します。

### `vc<graph::edge> inc.work()`

内部処理を行い、マージ情報を返します。
返る `edge` の `id` にはそのマージが起きた時刻 index が入ります。

## 境界・注意

- 一般用途の SCC ではなく、増加列に対する特殊なオフライン処理です。
- 詳しい利用側はこのリポジトリ内の実利用コードに合わせて読むのが安全です。

## 使用例

辺を時刻順に登録し、SCC がマージされた時刻を取り出します。

```cpp
incremental_scc inc(n);
for(auto [a,b]:edges){
    inc.push(a,b);
}

auto merges=inc.work();
for(auto e:merges){
    int u=e.from;
    int v=e.to;
    int time=e.id;
    // time 番目までの辺追加で u と v の SCC がマージされた
}
```
