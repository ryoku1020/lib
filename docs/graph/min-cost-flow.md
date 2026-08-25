---
title: min_info Cost flow
documentation_of: ../../graph/network_flow/min-cost-flow.hpp
---

# min_info Cost flow

非負コストの最小費用流です。
ポテンシャル付き最短路を繰り返して、`s` から `t` へちょうど `target` 流したときの最小コストを求めます。

## 使い方

```cpp
#include "graph/network_flow/min-cost-flow.hpp"

min_cost_flow<long long,long long> mcf(4);
mcf.add_edge(0,1,2,3);
mcf.add_edge(1,3,2,4);
mcf.add_edge(0,2,1,1);
mcf.add_edge(2,3,1,2);

auto [cost,flow]=mcf.run(0,3,2);
cout<<cost<<" "<<flow<<"\n";
```

## メソッド

- `min_cost_flow(int n=0)`
  頂点数 `n` で初期化します。

- `void add_edge(int a,int b,Cap cap,Cost cost)`
  有向辺 `a->b` を追加します。
  `cap`, `cost` はともに非負を仮定しています。

- `pair<Cost,Cap> run(int s,int t,Cap target)`
  `s` から `t` に高々 `target` だけ流したときの `(cost,flow)` を返します。
  `target` だけ流せない場合も、実際に流せた量とその最小コストを返します。

- `vc<tuple<int,int,int,Cap>> info()`
  各元辺に対する `(from,to,id,flow)` を返します。

## 境界・注意

- `cost>=0` を仮定しています。
- `add_edge(a,a,...)` は無視されます。
- `flow` ベクタは `run` のたびに再計算されます。

## 典型例

`run` の後に `info()` を見ると、どの辺にどれだけ流れたかを復元できます。

```cpp
auto info=mcf.info();
for(auto [u,v,id,f]:info){
    if(f>0){
        // 辺 u->v に f 流れた
    }
}
```
