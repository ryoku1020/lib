---
title: enumerate-triangle
documentation_of: ../../graph/misc/enumerate-tri.hpp
---

# enumerate-triangle

無向グラフ中の三角形を列挙します。

## 関数

### `void enumerate_triangle(const G<0,T>& g, F f)`

各三角形 `(a,b,c)` に対して `f(a,b,c)` を呼びます。

## 計算量

次数と頂点番号で各辺を向き付ける意図のアルゴリズムで、互換性のある単純無向グラフ型に対する想定計算量は `O(V log V+E sqrt(E))` 時間、`O(V+E)` 領域です。`V log V` は頂点の次数順ソート、`E sqrt(E)` は向き付け後の隣接辺走査によります。コールバックの処理時間は含みません。

## 境界・注意

- 無向グラフを前提としています。
- 同じ三角形は 1 回ずつ列挙されます。
- 自己ループや多重辺のない単純グラフを前提とします。
- テンプレート引数 `G` は `G<0,T>` と `G<1,T>` の両方を構築でき、`size()`, `edge_size()`, `all_edges()`, `deg()`, `operator[]` を持つ必要があります。`static_graph` を利用できます。

## 使用例

単純無向グラフ `g` に対する呼び出し方は次の通りです。

```cpp
#include"graph/misc/enumerate-tri.hpp"
using namespace ryoku;

long long cnt=0;
enumerate_triangle(g,[&](int a,int b,int c){
    cnt++;
});
```
