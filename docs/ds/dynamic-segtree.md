---
title: dynamic_segtree
documentation_of: ../../ds/segment_tree/dynamic-segtree.hpp
---

# dynamic_segtree

動的セグメント木です。
ノードを必要な分だけ生成しながら巨大な座標範囲を扱えます。
`is_persistent=true` で永続版になります。

## 型

```cpp
dynamic_segtree<info, sztype, is_persistent>
```

- `info` — 値モノイドの定義
- `sztype` — 座標の型。省略不可
- `is_persistent` — `true` なら永続 (各操作が新 root を返す)

## info の要件

```cpp
struct info{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

## コンストラクタ

### `dynamic_segtree(int n, value_type leaf = info::e())`

長さ `n` の領域を作ります（内部で最小の 2 冪に切り上げ）。
未生成ノードを含む各要素の初期値は `leaf` です。

- 計算量: `O(log n)`

## メソッド

### `node* seg.build()`

初期状態の root ノードを返します。

- 計算量: `O(1)`

### `node* seg.set(node* root, sztype i, value_type x)`

`root` のバージョンで位置 `i` を `x` に更新した新しい root を返します。

- 非永続版: `root` を破壊的に更新します。
- 永続版: `root` はそのまま保持し、新しい root を返します。
- 制約: `root!=nullptr`, `0<=i<N`
- 計算量: `O(log N)`

### `value_type seg.prod(node* root, int l, int r)`

`root` のバージョンで `op(a[l],...,a[r-1])` を返します。

- 制約: `0<=l<=r<=N`
- 計算量: `O(log N)`

### `sztype seg.max_right(node* root, sztype l, F f)`

`f(prod(l,r))` が真となる最大の `r` を返します。
`f(info::e())` は真である必要があります。

- 計算量: `O(log n)`

### `sztype seg.min_left(node* root, sztype r, F f)`

`f(prod(l,r))` が真となる最小の `l` を返します。
`f(info::e())` は真である必要があります。

- 計算量: `O(log n)`

## 境界・注意

- 区間は 0-indexed の半開区間 `[l,r)` です。
- `set` は `build` 後の非 null root が必要です。`prod` / `max_right` / `min_left` は null を未生成の初期木として扱えます。
- 永続版ではノード数が `O(Q log N)` になるのでメモリに注意してください。
- `N` は `n` を切り上げた 2 冪で、実装の `assert` は `[0,N)` まで許します。論理的な配列としては `[0,n)` だけを使ってください。
- テンプレートの `sztype` と異なり、コンストラクタ引数と内部の `N` は `int` です。`int` を超える座標範囲には対応していません。

## 使用例: 非永続・区間最小値

```cpp
#include "ds/segment_tree/dynamic-segtree.hpp"

struct info{
    using value_type = long long;
    static value_type op(value_type a, value_type b){ return min(a,b); }
    static value_type e(){ return (ll)4e18; }
};

dynamic_segtree<info, int, false> seg(1e9); // [0, 1e9) の範囲
auto root = seg.build();

root = seg.set(root, x, val);         // 1 点更新
auto ans = seg.prod(root, l, r);      // 区間最小値
```

## 使用例: 永続・1 点更新・区間和（永続版）

```cpp
struct info{
    using value_type = long long;
    static value_type op(value_type a, value_type b){ return a+b; }
    static value_type e(){ return 0; }
};

using Seg=dynamic_segtree<info,int,true>;
Seg seg(n);

vc<Seg::node*> roots;
roots.push_back(seg.build()); // version 0

// version i の更新
roots.push_back(seg.set(roots.back(), x, val));

// version i での区間和
auto ans = seg.prod(roots[i], l, r);

// version i の区間和 - version j の区間和 (区間内 count など)
auto diff = seg.prod(roots[i],l,r) - seg.prod(roots[j],l,r);
```
