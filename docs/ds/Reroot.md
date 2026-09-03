---
title: redp (Rerooting DP)
documentation_of: ../../ds/Reroot.hpp
---

# redp (Rerooting DP)

全方位木 DP（再根付き DP）のテンプレートです。
まず根 0 で部分木 DP をし、その後各頂点を根とした仮想的な DP 値を `O(N)` で計算します。

## 要件

```cpp
struct reroot{
    using V = ...; // 頂点のDP値の型
    using E = ...; // 辺のDP値の型（マージ対象）
    using edge = tree<unweighted>::edge; // 重み付きなら tree<Cost>::edge

    // 辺情報をマージ（E の単位元: id()）
    static E merge(E a, E b);

    // 辺集約値 a から頂点 v の DP 値を作る
    static V put_vertex(E a, int v);

    // 頂点の DP 値 a を辺 e に通したときの辺値を作る
    // e は tree<T>::edge（from, to, id, cost を持つ）
    static E put_edge(V a, const edge& e);

    // merge の単位元
    static E id();
};
```

データフロー:
```
子頂点の V → put_edge → E → merge で集約 → put_vertex → 親の V
```

## コンストラクタ

### `redp<reroot,T>(int n)`

頂点数 `n` で初期化します。

- `T` は辺コスト型。省略時は `unweighted`
- 制約: `n>=1`
- 計算量: `O(n)`

## メソッド

### `void dp.add_edge(int a,int b,cost_t cost=1,int id=-1)`

頂点 `a`-`b` 間に無向辺を追加します。

- `cost` — 両方向で共通の辺コスト
- `id` — 両方向で共通の辺番号。`-1` なら追加順の番号
- 制約: `0<=a,b<n`
- 計算量: ならし `O(1)`

`void add_edge(const edge& e)` で辺オブジェクトを直接追加するオーバーロードもあります。

### `vc<V> dp.calc()`

各頂点を根とした場合の DP 値を計算して返します。
`ans[v]` が頂点 `v` を根としたときの答えです。

- 計算量: `O(N)`（`merge` / `put_vertex` / `put_edge` が `O(1)` の場合）

## 境界・注意

- `put_edge` の第 2 引数は整数ではなく `tree<T>::edge` です。`e.id` と `e.cost` から辺番号・重みを取得できます。
- 辺は最初の `calc()` より前にすべて追加してください。内部では根 0 から 2 回の DFS を行います。
- 追加したグラフが連結な木である必要があります。閉路・多重に到達する辺があると正しく動かず、深い木では再帰スタックにも注意が必要です。

## 計算量

頂点数を `N` とすると、構築と使用メモリは `O(N)`、辺追加はならし `O(1)`、`calc()` は `O(N)` です（各ユーザー定義関数が `O(1)` の場合）。

## 使用例: 各頂点からの距離の最大値

```cpp
#include "ds/Reroot.hpp"

struct reroot{
    using V = int; // 頂点からの最大距離
    using E = int; // 辺を通した後の最大距離候補
    using edge = tree<unweighted>::edge;

    static E merge(E a, E b){ return max(a,b); }
    static V put_vertex(E a, int v){ return a; }
    static E put_edge(V a, const edge& e){ return a+1; }
    static E id(){ return 0; }
};

redp<reroot> dp(n);
for(int i=0;i<n-1;i++){
    dp.add_edge(u[i],v[i]);
}
auto ans = dp.calc(); // ans[v] = 頂点 v から最も遠い頂点への距離
```

## 使用例: 部分木サイズ（全方向）

```cpp
struct reroot{
    using V = int; // 仮想根のときの部分木サイズ
    using E = int;
    using edge = tree<unweighted>::edge;

    static E merge(E a, E b){ return a+b; }
    static V put_vertex(E a, int v){ return a+1; }
    static E put_edge(V a, const edge& e){ return a; }
    static E id(){ return 0; }
};
```
