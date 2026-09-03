---
title: scc
documentation_of: ../../graph/connectivity/scc.hpp
---

# scc

有向グラフの強連結成分分解を行います。
返り値は各頂点がどの成分に属するかを表す配列です。

## 関数

### `vc<int> scc(const G& g)`

有向グラフ `g` を強連結成分分解し、各頂点の成分 id を返します。

- 制約: `G::directed()==true`

## 計算量

`g[u]` と `g.inv(u)` の全走査がそれぞれ出次数・入次数に比例するグラフ型なら、Kosaraju 法により `O(N+M)` 時間、`O(N)` 補助領域です。2 回の DFS は再帰実装なので、最大 `O(N)` の再帰スタックも使います。

現行の `static_graph` は `buildinv()` の完了フラグを設定せず、`inv(u)` ごとに `O(N+M)` で逆 CSR を再構築します。そのまま渡した場合の現行実装上の最悪時間は `O(N(N+M))` です。

## 戻り値

- `res[v]`
  頂点 `v` が属する強連結成分 id

## 境界・注意

- `g.inv(u)` を使うので、逆辺を取得できる有向グラフを渡す必要があります。
- `N==0` では空配列を返します。
- 成分 id はトポロジカル順になっています。つまり `comp[u] < comp[v]` ならば、`u` の成分から `v` の成分へ有向辺が存在する可能性があります（逆はない）。縮約 DAG を使うときはこの順序を直接利用できます。
- 深いグラフでは再帰スタックの上限に注意してください。

## 使用例

```cpp
#include "graph/base.hpp"
#include "graph/connectivity/scc.hpp"

static_graph<1> g(n);
for(auto [u,v]:edges)g.add_edge(u,v);

auto comp=scc(g);
```

成分ごとに頂点を集めるときは次のようにします。

```cpp
int k=0;
for(int x:comp)k=max(k,x+1);
vector<vector<int>> groups(k);
for(int v=0;v<n;v++)groups[comp[v]].push_back(v);
```
