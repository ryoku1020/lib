---
title: DynamicSegtree
documentation_of: ../../ds/dynamic-segtree.hpp
---

# DynamicSegtree

動的セグメント木です。
ノードを必要な分だけ生成しながら巨大な座標範囲を扱えます。
`is_persistent=true` で永続版になります。

## 型

```cpp
DynamicSegtree<Info, sztype, is_persistent>
```

- `Info` — 値モノイドの定義
- `sztype` — 座標の型（デフォルト `int`）
- `is_persistent` — `true` なら永続 (各操作が新 root を返す)

## Info の要件

```cpp
struct Info{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
    // get2(depth): 深さ depth のノードが表す区間全体の「初期値」
    // 葉 (depth==0) なら leaf() の値、内部ノードは op(get2(depth-1),get2(depth-1))
    static value_type get2(int depth);
};
```

`get2(depth)` は、長さ `2^depth` の初期状態区間の集約値です。
`e()` で充填されている（初期値がモノイドの単位元）なら `get2(depth)=e()` で OK です。

## コンストラクタ

### `DynamicSegtree(int n)`

長さ `n` の領域を作ります（内部で最小の 2 冪に切り上げ）。

- 計算量: `O(log n)`

## メソッド

### `Node* seg.build()`

初期状態の root ノードを返します。

### `Node* seg.set(Node* root, sztype i, value_type x)`

`root` のバージョンで位置 `i` を `x` に更新した新しい root を返します。

- 非永続版: `root` を破壊的に更新します。
- 永続版: `root` はそのまま保持し、新しい root を返します。

### `value_type seg.prod(Node* root, int l, int r)`

`root` のバージョンで `op(a[l],...,a[r-1])` を返します。

## 使用例: 非永続・区間最小値

```cpp
#include "ds/dynamic-segtree.hpp"

struct Info{
    using value_type = long long;
    static value_type op(value_type a, value_type b){ return min(a,b); }
    static value_type e(){ return (ll)4e18; }
    static value_type get2(int){ return e(); } // 未生成ノードは INF
};

DynamicSegtree<Info, int, false> seg(1e9); // [0, 1e9) の範囲
auto root = seg.build();

root = seg.set(root, x, val);         // 1 点更新
auto ans = seg.prod(root, l, r);      // 区間最小値
```

## 使用例: 永続・1 点更新・区間和（永続版）

```cpp
struct Info{
    using value_type = long long;
    static value_type op(value_type a, value_type b){ return a+b; }
    static value_type e(){ return 0; }
    static value_type get2(int){ return 0; } // 未生成は 0
};

DynamicSegtree<Info, int, true> seg(n);

vc<Info::Node*> roots;
roots.push_back(seg.build()); // version 0

// version i の更新
roots.push_back(seg.set(roots.back(), x, val));

// version i での区間和
auto ans = seg.prod(roots[i], l, r);

// version i の区間和 - version j の区間和 (区間内 count など)
auto diff = seg.prod(roots[i],l,r) - seg.prod(roots[j],l,r);
```

## 注意

- 区間は 0-indexed の半開区間 `[l,r)` です。
- `prod` は `build` 後の root から呼ぶ必要があります（NULL は不可）。
- 永続版ではノード数が `O(Q log N)` になるのでメモリに注意してください。
