---
title: min_cost_flow
documentation_of: ../../graph/network_flow/min-cost-flow.hpp
---

# min_cost_flow

非負コストの最小費用流です。
ポテンシャル付き最短路を繰り返して、`s` から `t` へちょうど `target` 流したときの最小コストを求めます。

## 使用例

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

## 計算量

頂点数を $V$、追加辺数を $E$、`run` 中の増加路発見回数を $A$ とすると、ポテンシャル付き Dijkstra を 1 回の増加につき 1 回行うため、

- `add_edge`: amortized `O(1)`
- `run`: `O(A (V+E) log V)`
- `info`: `O(E)`

です。容量が非負整数なら、各増加で 1 以上流れるため `A<=target` であり、`run` は `O(target (V+E) log V)` とも評価できます。補助領域は `O(V+E)` です。

## 境界・注意

- `n>=0`, `0<=a,b,s,t<n`, `cap>=0`, `cost>=0`, `target>=0` が必要です。これらは `assert` で検査されます。
- 初期辺の負コストには対応していません。残余グラフでは負の逆辺を作るため、`Cost` には負数を表現できる符号付き型を使ってください。
- `add_edge(a,a,...)` は無視され、辺 ID も消費しません。
- `target==0` では `{0,0}` を返します。`s==t` では辺を使わず `{0,target}` を返す実装です。
- `target` を流し切れない場合、到達不能になった時点までに流せた最大量について `{最小費用,実流量}` を返します。成功判定は `flow==target` で行ってください。
- `flow` ベクタは `run` のたびに 0 から再計算されます。前回の流量を引き継ぎません。
- `info()` は `run()` の後に呼んでください。`run()` 後に辺を追加した場合は、もう一度 `run()` してから呼ぶ必要があります。
- 距離、ポテンシャル、`cost*flow` が `Cost` の範囲に収まる必要があります。

## 使用例: 辺ごとの流量

`run` の後に `info()` を見ると、どの辺にどれだけ流れたかを復元できます。

```cpp
auto info=mcf.info();
for(auto [u,v,id,f]:info){
    if(f>0){
        // 辺 u->v に f 流れた
    }
}
```
