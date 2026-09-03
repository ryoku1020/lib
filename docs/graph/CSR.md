---
title: csr_graph
documentation_of: ../../graph/CSR.hpp
---

# csr_graph

整数頂点だけを持つシンプルな CSR グラフです。
隣接先だけを軽く持ちたいときに使います。

## コンストラクタ

### `csr_graph(int n)`

頂点数 `n` で初期化します。

## メソッド

### `void g.add_edge(int u, int v)`

辺 `u->v` を追加します。

- 制約: `0<=u<n`, `0<=v`。通常のグラフとして使う場合は `v<n` も利用側で保証してください。
- 計算量: amortized `O(1)`

### `void g.build()`

追加した辺から CSR を構築します。
`build()` 後は `edges` は破棄されます。

- 計算量: `O(n+m)`

### `int g.empty(int u)`

頂点 `u` の隣接先が空かどうかを返します。
実装上の返り値型は `int` ですが、真偽値として使えます。

- 計算量: 初回は自動構築を含めて `O(n+m)`、以後 `O(1)`

### `auto g[u]`

頂点 `u` の隣接先配列を返します。

```cpp
for(int v:g[u]){
    // edge u -> v
}
```

- 計算量: view の取得は初回を除いて `O(1)`、走査は `O(out_deg(u))`

## 計算量まとめ

頂点数を $N$、辺数を $M$ とすると、構築は `O(N+M)` 時間・領域です。構築後の全隣接先の走査は合計 `O(N+M)` です。

## 境界・注意

- `g[u]` と `empty(u)` は必要なら内部で `build()` を呼ぶため、明示的な `build()` 前でも使えます。
- `build()` は 2 回目以降何もしません。構築後の `add_edge` は `assert` に失敗します。
- 辺情報は行き先だけです。重みや id は持ちません。
- 実装が検査するのは `v>=0` だけです。`v<n` が必要な用途では呼び出し側で保証してください。

## 使用例

```cpp
#include "graph/CSR.hpp"

csr_graph g(n);
for(auto [u,v]:edges)g.add_edge(u,v);
g.build();

for(int to:g[0]){
    // 0 -> to
}
```
