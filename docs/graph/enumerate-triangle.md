---
title: enumerate-triangle
documentation_of: ../../graph/enumerate-triangle.hpp
---

# enumerate-triangle

無向グラフ中の三角形を列挙します。

## 関数

### `void enumerate_triangle(const G<0,T>& g, F f)`

各三角形 `(a,b,c)` に対して `f(a,b,c)` を呼びます。

## 計算量

次数と頂点番号で各辺を向き付ける意図のアルゴリズムで、互換性のある単純無向グラフ型に対する想定計算量は `O(V log V+E sqrt(E))` 時間、`O(V+E)` 領域です。`V log V` は頂点の次数順ソート、`E sqrt(E)` は向き付け後の隣接辺走査によります。コールバックの処理時間は含みません。

ただし現行ヘッダは `g.m` を参照し、同じリポジトリの `static_graph` にはそのメンバがないため、`static_graph` でインスタンス化した利用可能な実装としての計算量は定義されません。

## 境界・注意

- 無向グラフを前提としています。
- 同じ三角形は 1 回ずつ列挙されます。
- 自己ループや多重辺のない単純グラフを前提とします。
- テンプレート引数 `G` は `G<0,T>` と `G<1,T>` の両方を構築でき、`size()`, `all_edges()`, `deg()`, `operator[]` に加えて公開メンバ `m` を持つ必要があります。
- このリポジトリの現行 `static_graph` は `edge_size()` を持つ一方で `m` を持たないため、そのまま渡すとコンパイルエラーになります。

## 使用例（想定 API）

互換グラフ型 `g` が用意できた場合の呼び出し方は次の通りです。現行の `static_graph` を `g` に使うことはできません。

```cpp
#include "graph/enumerate-triangle.hpp"

long long cnt=0;
enumerate_triangle(g,[&](int a,int b,int c){
    cnt++;
});
```
