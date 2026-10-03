---
title: k 番目最短 walk | kthshortestwalk
documentation_of: ../../graph/path/kth-shortest-walk.hpp
keywords: kthshortestwalk, k 番目最短, walk, paths
---

# k 番目最短 walk (`kthshortestwalk`)

始点 `s` から終点 `t` へ進む walk の距離を昇順に列挙します。頂点・辺の再訪を許すため、単純路の k 番目を探す API ではありません。

```cpp
#include "graph/path/kth-shortest-walk.hpp"

auto lengths = kthshortestwalk<long long>(g, s, t, k);
for (int i = 0; i < k; ++i) {
    if (lengths[i] == -1) continue; // i+1 番目の walk は存在しない
    // lengths[i] は i+1 番目に短い距離
}
```

`kthshortestwalk<T>(g,s,t,k)` は長さ `k` の `vc<T>` を返します。`k==0` なら空 vector。候補が足りないときは残りを `-1` で埋めるので、`T` は `-1` を表せる型にしてください。`s,t` は `[0,g.size())`、辺の `cost` は非負で、距離加算が `T` の範囲内であることが必要です。辺 ID は `[0,g.edge_size())` の一意な連番にします。

逆辺列挙 `g.inv(v)` を使って終点から距離を計算し、最短路木以外の辺による候補を heap で列挙します。heap 操作を含む概算時間は `O((V+E) log V + (E+k) log(E+k))`、一時領域は `O(V+E+k)` 級です。leftist heap ノードは解放されないため、同一プロセスで大規模呼び出しを繰り返すと確保領域が残ります。

距離だけの通常の単一始点最短路は [Dijkstra](advanced.md#経路) を使います。負辺を含むグラフには使えません。
