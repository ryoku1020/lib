---
title: scc
documentation_of: ../../graph/scc.hpp
---

# scc

有向グラフの強連結成分分解を行います。
返り値は各頂点がどの成分に属するかを表す配列です。

## 関数

### `vc<int> scc(const G& g)`

有向グラフ `g` を強連結成分分解し、各頂点の成分 id を返します。

- 制約: `G::directed()==true`
- 計算量: `O(n+m)`

## 戻り値

- `res[v]`
  頂点 `v` が属する強連結成分 id

## 使用例

```cpp
#include "graph/base.hpp"
#include "graph/scc.hpp"

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

## 注意

- `g.inv(u)` を使うので、逆辺を取得できる有向グラフを渡す必要があります。
- id の番号自体には意味を持たせない方が安全です。必要なら DAG を作ってから自分で扱います。
