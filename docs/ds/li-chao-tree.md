---
title: li_chao_tree
documentation_of: ../../ds/li_chao_tree/li-chao-tree.hpp
---

# li_chao_tree

Li Chao tree です。
`[0, n)` の整数 x 座標に対して、直線（または線分）の追加と、指定した x での最小値（または最大値）クエリを `O(log n)` で行えます。

座標範囲が固定でよい場合はこれを使ってください。
座標が大きい非負整数の場合は [dynamic_li_chao_tree](dynamic-li-chao-tree.md)、
クエリ座標が事前にわかっている場合は [compressed_li_chao_tree](compressed-li-chao-tree.md) が使えます。

## テンプレート引数・直線型

`li_chao_tree<Line,T,ismin>` と指定します。`T` は座標・評価値の型、`ismin` は最小値なら `true`（既定）、最大値なら `false` です。

`Line` は `T eval(T x)const` と `static Line id()` を持つ型を渡します。
追加する関数同士の大小関係が座標順に高々1回しか切り替わらないことが必要です。通常は次のような直線型を使います。

```cpp
template<class T>
struct chtline{
    T a,b;
    int idx=-1;
    T eval(T x)const{
        return a*x+b;
    }
    static chtline id(){
        return {0,inf<T>,-1};
    }
};
using LCT=li_chao_tree<chtline<long long>,long long,true>;
```

`id()` は空ノードの初期化に使います。空ノードは比較・評価から除外するため、最大値モードでも上の `id()` をそのまま使えます。`idx` などの付加情報も保持されますが、`query` は評価値を返します。

## コンストラクタ

### `li_chao_tree(int n)`

x 座標の範囲 `[0, n)` で Li Chao tree を作ります。

- 計算量: `O(n)`

## メソッド

### `void lct.add_line(Line a)`

直線 `a` を全体に追加します。

- 計算量: `O(log n)`

### `void lct.add_segment(Line a, int l, int r)`

x ∈ `[l, r)` の範囲にのみ有効な線分 `a` を追加します。

- 制約: `0 <= l <= r <= n`
- 計算量: `O(log^2 n)`

### `T lct.query(T x)`

x における最小値（`ismin=true`）または最大値（`ismin=false`）を返します。

- 制約: `0 <= x < n`
- 計算量: `O(log n)`

## 境界・注意

- x 座標は整数で `[0, n)` の範囲です。
- 有効な直線がない座標では、最小値モードは `inf<T>`、最大値モードは `-inf<T>` を返します。評価値はこの範囲に収まるようにしてください。
- 内部的には n を 2 のべき乗に切り上げています。

## 使用例: CHT（Convex Hull Trick）

直線 `y = ax + b` の `x ∈ [0, N)` での最小値を管理します。

```cpp
#include "ds/li_chao_tree/li-chao-tree.hpp"

// chtline は上の定義を使用
li_chao_tree<chtline<long long>,long long,true> lct(N);

lct.add_line({a, b}); // y = ax + b を追加
long long ans = lct.query(x);
```
