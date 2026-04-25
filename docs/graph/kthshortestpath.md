---
title: kthshortestpath
documentation_of: ../../graph/kthshortestpath.cpp
---

# kthshortestpath

`s` から `t` への k-shortest paths の長さを先頭から `k` 個返します。
Eppstein 系の発想で leftist heap を使っています。

## 関数

### `vc<T> kthshortestpath(G g, int s, int t, int k)`

長さを小さい順に `k` 個返します。
存在しないぶんは `-1` で埋まります。

## 使用例

```cpp
#include "graph/kthshortestpath.cpp"

auto ds=kthshortestpath<long long>(g,s,t,k);
```

## 注意

- `g.inv(v)` が使えるグラフを仮定しています。
- ヘッダではなく `.cpp` に実装されています。
