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
- `s == t` のとき `0` を返します
- 計算量: `O(V^2 * E)` 一般、単位容量グラフでは `O(E * sqrt(V))`

## 境界・注意

- `cap` は非負整数を前提としています。負の容量を渡した場合の動作は未定義です。
- `run` を複数回呼ぶと前回の残余グラフを引き継ぎます。通常は 1 度だけ呼んでください。

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
