---
title: flow
documentation_of: ../../graph/network_flow/flow.hpp
---

# flow

Dinic 法による最大流です。

## 型

```cpp
flow<T>
```

- `T` — 容量・流量の型（`int`, `long long` など）

## コンストラクタ

### `flow<T>(int n)`

頂点数 `n` のフローネットワークを作ります。

## メソッド

### `void mf.add_edge(int a, int b, T cap)`

有向辺 `a -> b` を容量 `cap` で追加します。
逆辺（容量 0）は自動追加されます。

- 制約: `0 <= a, b < n`, `cap >= 0`
- 計算量: `O(1)` amortized

### `T mf.run(int s, int t)`

`s` から `t` への最大流値を返します。

- 制約: `0 <= s, t < n`
- 計算量: `O(V^2 * E)`

### `vc<tuple<int,int,int,T>> mf.info()`

各元辺について `(from,to,id,flow)` を追加順に返します。

- 制約: `run()` の後
- 計算量: `O(E)`

### `vc<bool> mf.min_cut(int s)`

最後の `run()` が作った残余グラフで `s` から到達可能な頂点を返します。`s-t` 最大流の直後なら、`true` 側が最小カットの始点側です。

- 制約: `run()` の後、`0<=s<n`
- 計算量: `O(V+E)`

## 計算量まとめ

一般容量での `run` は `O(V^2 E)` 時間、`O(V+E)` 補助領域です。単位容量に対するより強い評価はグラフの条件によって異なるため、一般上界を基準にしてください。

## 境界・注意

- `cap` は非負整数を前提としています。負の容量を渡した場合の動作は未定義です。
- 自己ループ `add_edge(a,a,cap)` は無視され、辺 ID も消費しません。
- `s==t` では増加量 `numeric_limits<T>::max()` を繰り返し加えるため、`run` が終了しません。必ず `s!=t` としてください。
- `run` は呼ぶたびに全辺の流量を 0 に戻して計算し直し、前回の残余グラフを引き継ぎません。
- `info()` と `min_cut()` は `run()` の後に呼んでください。辺を追加した場合は再び `run()` が必要です。
- 再帰 DFS を使うため、深いレベルグラフでは `O(V)` の再帰スタックを使います。

## 使用例

```cpp
#include "graph/network_flow/flow.hpp"

flow<long long> mf(n);
mf.add_edge(s, a, 3);
mf.add_edge(s, b, 4);
mf.add_edge(a, t, 2);
mf.add_edge(b, t, 5);
mf.add_edge(a, b, 1);

auto ans = mf.run(s, t); // 最大流値
```
