---
title: DynamicLazySegtree
documentation_of: ../../ds/dynamic-lazy-segtree.hpp
---

# DynamicLazySegtree

動的遅延セグメント木です。
通常の遅延セグメント木と異なり、座標を `sztype`（デフォルト `int`）で指定でき、
$2^{63}$ 程度の巨大な範囲を「ノードを必要な分だけ生成」しながら扱えます。

## 要件

`Info` と `Tag` は通常の `LazySegtree` と同様ですが、追加で次が必要です。

### `Info` の追加要件

```cpp
struct Info{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

未生成ノードの値は、コンストラクタで渡した `leaf` から内部で計算されます。

### `Tag` の要件

通常の `LazySegtree` と同じです。

```cpp
struct Tag{
    using lazy_type=...;
    static value_type Apply(value_type x, lazy_type f);
    static lazy_type Merge(lazy_type old_tag, lazy_type new_tag);
    static lazy_type id();
    static constexpr bool commute=false; // optional
};
```

`Tag::commute` を `true` にすると、任意の 2 つのタグが可換であることを表します。
この場合、部分区間更新で親の遅延を子へ伝播せずに処理します。省略時は従来どおり伝播します。

## コンストラクタ

### `DynamicLazySegtree(sztype n, value_type leaf = Info::e())`

長さ `n` の領域を作ります（内部で最小の 2 冪に切り上げ）。
未生成ノードを含む各要素の初期値は `leaf` です。

- 計算量: `O(log n)`

## メソッド

### `void seg.set(sztype i, value_type x)`

位置 `i` を値 `x` に更新します。

- 制約: `0<=i<n`
- 計算量: `O(log n)` amortized（ノード生成含む）

### `value_type seg.prod(sztype l, sztype r)`

`op(a[l], ..., a[r-1])` を返します。

- 制約: `0<=l<=r<=n`
- 計算量: `O(log n)`

### `void seg.apply(sztype l, sztype r, lazy_type x)`

`l<=i<r` の各要素に作用素 `x` を適用します。

- 制約: `0<=l<=r<=n`
- 計算量: `O(log n)` amortized

## 境界・注意

- 内部の node pool は最大 `1.5e7` ノードで固定されています（`MAX_NODE=1.5e7`）。クエリ数が多い場合はオーバーフローに注意。
- 区間は 0-indexed の半開区間 `[l,r)` です。
- `sztype` は座標の型で、デフォルト `int`。`ll` を使う場合は `DynamicLazySegtree<Info,Tag,ll>` のように指定します。

## 使用例: 区間加算・区間和（$10^{18}$ 座標）

葉の初期値を 0 とし、区間加算・区間和を $[0, 10^{18})$ の範囲で行う例です。

```cpp
#include "ds/dynamic-lazy-segtree.hpp"

using ll = long long;

struct Info{
    using value_type = ll; // {sum}
    static value_type op(value_type a, value_type b){ return a+b; }
    static value_type e(){ return 0; }
};

struct Tag{
    using lazy_type = ll;
    static value_type Apply(value_type x, lazy_type f){ return x+f; }
    static lazy_type Merge(lazy_type a, lazy_type b){ return a+b; }
    static lazy_type id(){ return 0; }
};

DynamicLazySegtree<Info,Tag,ll> seg(1e18);
seg.apply(l, r, x);          // [l,r) に x を加算
auto s = seg.prod(l, r);      // [l,r) の和
```

## 使用例: 葉の初期値が 1（区間和 = 長さ）

```cpp
struct Info{
    using value_type = ll;
    static value_type op(value_type a, value_type b){ return a+b; }
    static value_type e(){ return 0; }
};

DynamicLazySegtree<Info,Tag,ll> seg(1e18,1);
```
