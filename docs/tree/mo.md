---
title: 木上の Mo | motree_vertex / motree_edge
documentation_of: ../../ds/sequence/motree-vertex.hpp
keywords: 木上の Mo, motree_vertex, motree_edge, Mo's algorithm, path query
---

# 木上の Mo (`motree_vertex`, `motree_edge`)

木上のパス問い合わせを Euler Tour の Mo 順に並べ、現在のパスに頂点または辺を追加・削除しながら処理します。パス上の値に対する可逆な `add` / `erase` を用意できる場合に使います。

```cpp
#include "ds/sequence/motree-vertex.hpp"

tree<unweighted> g(n);
for (auto [u,v] : edges) g.add_edge(u,v);
motree_vertex mo(q,g);
for (auto [u,v] : queries) mo.add(u,v);

mo.run(
    [&](int v) { /* 頂点 v を現在集合へ加える */ },
    [&](int v) { /* 頂点 v を現在集合から外す */ },
    [&](int id) { answer[id] = current_answer; }
);
```

`motree_edge` の include と構築方法は同じで、callback の引数は頂点ではなく辺 ID です。

## API と条件

- `motree_vertex(int q, const tree<unweighted>& g)` / `motree_edge(int q, const tree<unweighted>& g)` は `q` 件のクエリ用に木をコピーします。
- `add(s,t)` はパス両端を登録し、追加順が callback の `id` になります。頂点は `[0,n)`。
- `run(add,erase,answer)` は全クエリを処理します。現在パスが変わるとき、頂点版は頂点番号、辺版は元 tree の edge ID を callback に渡します。
- `answer(id)` は元の追加順のクエリ ID で呼びます。
- 実装は根 `0` で Euler Tour / LCA を構築します。入力は連結な木を想定し、`n>=1`。
- `add` と `erase` は互いに逆操作になるよう設計します。現在集合に対して可換な集約なら、Mo の順序変更に合わせて追加・削除できます。

## 計算量・注意

`n` 頂点、`q` クエリに対し、Mo の移動量は概ね `O(n sqrt(q))`、加えて木の前処理 `O(n log n)`。callback が `O(1)` ならこの程度です。実装は頂点版・辺版ともに `mo` の自動 block width を使います。

`motree_edge` は辺 ID で状態管理するため、辺を木に追加するときに明示 ID を指定する場合は一意な ID を使ってください。`tree` は `static_graph` の既定追加順 ID を使えます。

関連: 配列区間向け [Mo](../ds/mo.md)、部分木への小さい袋併合は [DSU on tree](dsu-on-tree.md)、一般の木パス分解は [HLD](base.md)。
