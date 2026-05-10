---
title: Redp (Rerooting DP)
documentation_of: ../../ds/Reroot.hpp
---

# Redp (Rerooting DP)

全方位木 DP（再根付き DP）のテンプレートです。
まず根 0 で部分木 DP をし、その後各頂点を根とした仮想的な DP 値を `O(N)` で計算します。

## 要件

```cpp
struct Reroot{
    using V = ...; // 頂点のDP値の型
    using E = ...; // 辺のDP値の型（マージ対象）

    // 辺情報をマージ（E の単位元: id()）
    static E merge(E a, E b);

    // 辺集約値 a から頂点 v の DP 値を作る
    static V put_vertex(E a, int v);

    // 頂点 v の DP 値 a を辺 e に通したときの辺値を作る
    static E put_edge(V a, int e);

    // merge の単位元
    static E id();
};
```

データフロー:
```
子頂点の V → put_edge → E → merge で集約 → put_vertex → 親の V
```

## コンストラクタ

### `Redp<Reroot>(int n)`

頂点数 `n` で初期化します。

## メソッド

### `void dp.add_edge(int a, int b, int idx, int xdi)`

頂点 `a`-`b` 間に無向辺を追加します。
- `idx` : `a → b` の辺番号
- `xdi` : `b → a` の辺番号

辺番号が不要な場合は任意の値（例: 0）を渡して `put_edge` 内で無視すれば OK です。

### `vc<V> dp.calc()`

各頂点を根とした場合の DP 値を計算して返します。
`ans[v]` が頂点 `v` を根としたときの答えです。

- 計算量: `O(N)`

## 使用例: 各頂点からの距離の最大値

```cpp
#include "ds/Reroot.hpp"

struct Reroot{
    using V = int; // 頂点からの最大距離
    using E = int; // 辺を通した後の最大距離候補

    static E merge(E a, E b){ return max(a,b); }
    static V put_vertex(E a, int v){ return a; }
    static E put_edge(V a, int e){ return a+1; } // 辺を渡るたびに +1
    static E id(){ return 0; }
};

Redp<Reroot> dp(n);
for(int i=0;i<n-1;i++){
    dp.add_edge(u,v,i,i); // 辺番号は使わないので同じでも OK
}
auto ans = dp.calc(); // ans[v] = 頂点 v から最も遠い頂点への距離
```

## 使用例: 部分木サイズ（全方向）

```cpp
struct Reroot{
    using V = int; // 仮想根のときの部分木サイズ
    using E = int;

    static E merge(E a, E b){ return a+b; }
    static V put_vertex(E a, int v){ return a+1; }
    static E put_edge(V a, int e){ return a; }
    static E id(){ return 0; }
};
```

## 注意

- `add_edge` に渡す辺番号 `idx` / `xdi` は `put_edge` に渡ってくる `e` 引数です。
  辺に重みがある場合などに使います。不要なら 0 固定で OK。
- 内部は根 0 からの DFS のあと、トポロジカル順で逆方向に計算します。
- グラフは「木」である必要があります（閉路があると正しく動きません）。
