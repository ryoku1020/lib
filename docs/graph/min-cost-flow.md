---
title: Min Cost Flow
documentation_of: ../../graph/min-cost-flow.hpp
---

# Min Cost Flow

非負コストの最小費用流です。
ポテンシャル付き最短路を繰り返して、`s` から `t` へちょうど `target` 流したときの最小コストを求めます。

## 使い方

```cpp
#include "graph/min-cost-flow.hpp"

MinCostFlow<long long,long long> mcf(4);
mcf.add_edge(0,1,2,3);
mcf.add_edge(1,3,2,4);
mcf.add_edge(0,2,1,1);
mcf.add_edge(2,3,1,2);

auto ans=mcf.run(0,3,2);
if(ans){
    cout<<*ans<<"\n";
}
```

## メソッド

- `MinCostFlow(int n=0)`
  頂点数 `n` で初期化します。

- `void add_edge(int a,int b,Cap cap,Cost cost)`
  有向辺 `a->b` を追加します。
  `cap`, `cost` はともに非負を仮定しています。

- `optional<Cost> run(int s,int t,Cap target)`
  `s` から `t` に `target` だけ流したときの最小コストを返します。
  流せない場合は `nullopt` を返します。

- `vc<tuple<int,int,int,Cap>> Info()`
  各元辺に対する `(from,to,id,Flow)` を返します。

## 典型例

`run` の後に `Info()` を見ると、どの辺にどれだけ流れたかを復元できます。

```cpp
auto info=mcf.Info();
for(auto [u,v,id,f]:info){
    if(f>0){
        // 辺 u->v に f 流れた
    }
}
```

## 注意

- `cost>=0` を仮定しています。
- `add_edge(a,a,...)` は無視されます。
- `Flow` ベクタは `run` のたびに再計算されます。
