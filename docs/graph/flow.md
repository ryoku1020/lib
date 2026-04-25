---
title: flow
documentation_of: ../../graph/flow.hpp
---

# flow

Dinic 法による最大流です。

## コンストラクタ

### `flow<T>(int n)`

頂点数 `n` のフローネットワークを作ります。

## メソッド

### `void mf.add_edge(int a, int b, T cap)`

有向辺 `a->b` を容量 `cap` で追加します。
逆辺は容量 0 で自動追加されます。

- 制約: `0<=a,b<n`
- 計算量: amortized `O(1)`

### `T mf.work(int s, int t)`

`s` から `t` への最大流を返します。

- 制約: `0<=s,t<n`
- 計算量: 一般には Dinic 法の計算量

## 使用例

```cpp
#include "graph/flow.hpp"

flow<long long> mf(n);
mf.add_edge(s,a,3);
mf.add_edge(a,t,2);
mf.add_edge(s,b,4);
mf.add_edge(b,t,5);

auto ans=mf.work(s,t);
```

## 注意

- 現在の実装名は `ae` ではなく `add_edge` です。
- `work` を複数回呼ぶと前回の残余グラフ状態を引き継ぐので、通常は 1 回だけ呼ぶ想定です。
