---
title: CsrGraph
documentation_of: ../../graph/csr.hpp
---

# CsrGraph

整数頂点だけを持つシンプルな CSR グラフです。
隣接先だけを軽く持ちたいときに使います。

## コンストラクタ

### `CsrGraph(int n)`

頂点数 `n` で初期化します。

## メソッド

### `void g.add_edge(int u, int v)`

辺 `u->v` を追加します。

### `void g.build()`

追加した辺から CSR を構築します。
`build()` 後は `edges` は破棄されます。

- 計算量: `O(n+m)`

### `int g.empty(int u)`

頂点 `u` の隣接先が空かどうかを返します。
実装上の返り値型は `int` ですが、真偽値として使えます。

### `auto g[u]`

頂点 `u` の隣接先配列を返します。

```cpp
for(int v:g[u]){
    // Edge u -> v
}
```

## 使用例

```cpp
#include "graph/csr.hpp"

CsrGraph g(n);
for(auto [u,v]:edges)g.add_edge(u,v);
g.build();

for(int to:g[0]){
    // 0 -> to
}
```

## 注意

- `build()` 前に `g[u]` や `empty(u)` は使えません。
- 辺情報は行き先だけです。重みや id は持ちません。
