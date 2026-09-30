---
title: グラフ追加実装 | 連結性・色付け・経路
documentation_of: ../../graph/connectivity/lowlink.hpp
keywords: lowlink, bridges, biconnected, directed_mst, Eulerian, dijkstra, kthshortestwalk, cycle_detection, stnumbering
---

# グラフ追加実装

このページは個別ページのないグラフ機能の入口です。グラフは主に [`graph/base.hpp`](base.md) の `static_graph` / `tree` 形式を使います。関数がグラフを値渡しするものと参照で受け取るものがあるため、宣言を確認してください。

## 連結性・分解

| API | 結果と条件 | 計算量 |
|---|---|---|
| `lowlink<G> ll(g)` | 無向グラフの lowlink。構築時に DFS。`isbridge(id)` は辺が橋なら真。`twoedge_component()` / `twovertex_component()` は後述の成分対応と森を返す。 | `O(V+E)` 構築・各分解、`isbridge` は `O(1)` |
| `all_cycle(g)` | `pair<vvc<int>,vvc<int>>`。`first[i]` は閉路の頂点列、`second[i]` は対応する辺 ID 列。全単純閉路の列挙ではない。 | `O(V+E)` |
| `cycle_decomposition(p)` | 順列 `i -> p[i]` を巡回列に分解し、各巡回の頂点列（始点を重複させない）を返す。`p` は `[0,n)` 上の置換。 | `O(n)` |
| `contraction(g, group)` | `group[v]` で指定した同一グループを縮約したグラフと、頂点から縮約後の番号への対応を返す。`group.size()==g.size()`。入力は値渡し。 | `O(V+E)` |
| `taketree<T>(g)` | 各連結成分の DFS 木を `tree<T>` で返す。無向グラフ想定。 | `O(V+E)` |
| `stnumbering(g,s,t)` | 2連結無向グラフの st-numbering を返す。失敗・前提不成立時は空 vector。成功時 `res[v]` は頂点 `v` の順位で、`res[s]=0`, `res[t]=n-1`。 | `O(V+E)` |

`lowlink<G> ll(g)` は無向グラフをコピーして保持し、構築時に DFS を実行します。`isbridge(id)` は `g.get_edge(id)` を参照するので、辺 ID は元辺列の `[0,E)` 連番にしてください。`twoedge_component()` の返り値 `edgecomponent` は `toid[v]`（各頂点の 2-edge-connected component 番号）と component tree `comp`。`twovertex_component()` の `vertexcomponent` は `egs[i]`（第 i ブロックを構成する元辺 ID 列）と block-cut forest `comp` を返します。forest の元頂点は `[0,n)`、ブロック頂点は `[n,n+egs.size())` です。`contraction` の `group` 番号は連続していなくてもよいですが、結果の番号対応は返却された第 2 成分で読み取ります。`all_cycle` は `e.id` を添字として使い、自己ループも正しく扱わないため、辺 ID 連番の単純無向グラフに限ってください。

## 木の有向化・最小 arborescence

`directed_mst(g, root)` は root から全頂点へ到達する最小有向全域木（minimum arborescence）の辺を返します。頂点数 1 なら空 vector が成功結果です。

```cpp
#include "graph/connectivity/directed-mst.hpp"

auto edges = directed_mst(g, root);
```

- 入力は有向重み付きグラフで、辺の `cost` は `long long` に変換可能であること。root は `[0,n)`。辺 ID は `g.get_edge(id)` で参照できるよう `[0,E)` の一意な連番にしてください。
- 返り値は選ばれた元グラフの edge の vector。全頂点へ到達できないと空 vector を返すため、`n>1` では辺数 `n-1` か確認する。
- Edmonds/Chu–Liu 型の縮約と skew heap を使い、時間 `O(E log V)`、作業領域は `O(V+E)` 級。heap node の pool は型ごとに static で、関数を抜けても解放されません。

`taketree(g)` は一般の DFS 森を作る関数で、有向グラフの最小 arborescence とは別です。

## 経路

```cpp
#include "graph/path/dijkstra.hpp"
#include "graph/path/restore-path.hpp"

auto dist = dijkstra<long long>(g, vc<int>{s});
auto [vertices, edges] = restore_path(g, dist, s, t);
```

- `dijkstra<T>(g, starts)` は始点 vector の各頂点を距離 0 とした距離 vector を返す。単一始点のつもりで `dijkstra<T>(g,s)` と呼ぶ overload は、実装の template 引数 `F` を推論できずコンパイルできない。単一始点は `dijkstra<T>(g, vc<int>{s})` と書くか、型まで明示して `dijkstra<T, decltype(g), int>(g,s)` と呼ぶ。
- 全辺の重みが非負であること。到達不能は `inf<T>`。二分ヒープ版の計算量は `O((V+E) log(E+1))`、距離 vector は `O(V)`。
- `slow_dijkstra<T>(g,starts)` は同じ距離を線形走査で計算する密グラフ向け実装。`O(V^2+E)`。
- `restore_path(g, dist, s, t)` は距離ラベル `dist` を使って復元し、`{頂点列, 辺列}` を返す。到達不能時は両方空。辺の重みは非負を前提とした緩和判定。
- `shortest_path<T>(g,s,t)` はソース上 `{ {頂点列, 辺列}, 距離 }` を返す設計だが、現在の内部呼出 `dijkstra<T>(g,s)` が上記 template 推論に失敗するため、そのままではコンパイルできない。
- `findnegcycle<T>(g)` は全頂点から到達可能な負閉路の頂点列を返す。なければ空。全頂点を初期距離 0 とするため、特定始点に限定しない。`O(VE)`。
- `cycle_detection(g)` は有向・無向グラフの閉路を 1 つ見つけ、`{頂点列,辺 ID 列}` を返す。閉路なしは空の pair。閉路列では始点を重ねない。
- `eulerian(g)` は Euler trail を `optional<pair<頂点列,辺列>>` で返す。無向・有向の両方に対応し、辺を使い切る trail がないとき `nullopt`。辺なしでは `{{0}, {}}` を返すため、頂点数 0 のグラフに適用する用途には向かない。辺 ID は `[0,E)` の一意な連番が必要。
- `kthshortestwalk<T>(g,s,t,k)` は `s` から `t` への walk の距離を小さい順に列挙し、先頭 `k` 個を返す。walk は頂点・辺の再訪を許す。存在しない順位は `-1` で埋める。`k==0` なら空 vector。非負重みを想定し、heap による列挙は `O((E+k) log(E+k))` 級。

## 彩色・部分構造

| API | 用途・返り値 | 制約 |
|---|---|---|
| `chromatic_number(g)` | 単純無向グラフの彩色数を返す | `n < 32`。subset DP `O(n 2^n)` を3回。法を乱択する片側 Monte Carlo で、法が割り切ると正解より大きい値が残る可能性あり |
| `mis(g)` | 単純無向グラフの最大独立集合の頂点番号を返す | 指数時間。実装は `O(2^n)` 級探索 |
| `havel_hakimi(deg)` | 次数列を実現する単純無向グラフの辺リストを返す | 実現不能なら `nullopt`; 頂点番号は `[0,n)` |
| `bipatite_edge_coloring(edges,L,R)` | 二部グラフの各辺に色番号を割り当てた vector を返す | `L,R>=1`、左右頂点番号はそれぞれ `[0,L)`, `[0,R)`。返り値 `ans[i]` は `edges[i]` の色番号 `[0,D)`（`D` は最大次数）。最大次数以下の色数 |
| `enumerate_clique(g, f)` | 空でないすべての clique を `f(const vc<int>&)` に渡す | 無向・単純グラフを想定。総出力サイズ以上の時間 |
| `enumerate_triangle(g, f)` | 各三角形を `f(a,b,c)` に渡す | 単純無向グラフ。三頂点の並び順は実装の向き付けによる |

`bipatite_edge_coloring` はソース上の綴りが `bipatite` です。`bipartite_match` とは別機能で、前者は辺彩色、後者は最大マッチングです。

## 関連

[SCC](scc.md) は有向グラフの強連結成分、[二部マッチング](bipartite-match.md) は最大マッチング、[最大流](flow.md) は容量付きネットワーク向けです。
