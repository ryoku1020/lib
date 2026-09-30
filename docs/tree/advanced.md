---
title: 木追加 API | Cartesian Tree・Virtual Tree
documentation_of: ../../tree/cartesian-tree.hpp
keywords: cartesian_tree, virtualtree, namori, Cartesian Tree, functional graph
---

# 木の追加 API

HLD や LCA を使う一般木は [`tree`](base.md) を参照してください。このページは配列から作る Cartesian tree、頂点集合を圧縮する virtual tree、単純サイクルを持つ graph 向け分解です。

## Cartesian tree

```cpp
#include "tree/cartesian-tree.hpp"

auto [t, root] = cartesian_tree<1>(a); // min-heap 型
```

`cartesian_tree<mintop>(a)` は `{tree<unweighted>, root}` を返します。`mintop != 0` なら親の値が子以下、`mintop == 0` なら親の値が子以上となるように作ります。木の頂点番号は元配列の添字です。`a` は空でない必要があります。時間・領域 `O(n)`。

同じ値があるときは stack の pop 条件が `>=` / `<=` なので、同値要素の親子方向も入力順に依存します。

## Virtual tree

```cpp
#include "tree/virtual-tree.hpp"

virtualtree<unweighted> vt(g);
auto view = vt.call(terminals, 1); // 双方向辺を格納
for (int u : terminals) for (int v : view[u]) { /* 辺 u-v */ }
```

- `virtualtree<T> vt(tree<T> g)` は元木のコピーを保持します。呼出時に元木の HLD 情報を構築します。
- `call(vs,both)` は `vs` 内の頂点とそれらの隣接 LCA を含む圧縮木の隣接リスト view を返します。`both!=0` なら辺を両方向に格納し、0 なら親から子方向のみです。
- 頂点番号は元の木の番号をそのまま使います。未採用頂点の隣接リストは空です。実装は根 `0` も候補に含めます。
- `call` は内部バッファを再利用します。次の `call()` や `clearg()` の後は前の view の内容が変わります。`vs` は値渡しで並べ替えられますが、元の vector は変更しません。
- `k=|vs|` のときソートと LCA を含め `O(k log n)`、出力領域 `O(k)`。
- `vs` が空なら空 view を返します。入力頂点は `[0,n)`。

## Namori decomposition

`namori<T> nm(n)` は連結な単純無向な n 頂点 n 辺グラフを想定し、`add_edge(u,v,w)` の後 `build()` します。サイクル頂点 `cyc` と、サイクルから各頂点へ伸びる木の情報を構築します。

- `group[v]` は v が属するサイクル根の番号、`incycle[v]` は v がサイクル上か、`parinv[v]` はサイクル上の位置、`inner_id[v]` は対応する根付き木内の番号。
- `cyc[i]` と `cycw[i]` はサイクルの i 番目頂点・その次へ進む辺重みです。`t[i]` はそのサイクル根を含む木です。
- `path_decomposition(a,b)` は `{start,end,type}` の配列を返し、端点は元の頂点番号です。`type==0` はサイクル根付き木内の部分、`type==1` はサイクル上の部分を示します。これは頂点列そのものではなく、返った区間を使って経路集約を組み立てるための分解です。
- 構築は `O(n)`。このクラスの `build()` は単純サイクルを持つグラフを前提とし、その条件を検証しません。

## 最大長方形

矩形 API は [幾何の追加実装](../geometry/advanced.md) を参照してください。
