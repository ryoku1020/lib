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
    static value_type leaf(); // 葉 1 要素の初期値
    // bylen: 長さ len の「初期状態の区間」の集約値
    static value_type bylen(sztype len, const vc<value_type>& db);
};
```

`bylen` は、ノードが生成されていない（= 初期状態の）長さ `len` の区間に対して
`op(leaf(), leaf(), ..., leaf())` を返す関数です。
`db[i]` には「長さ `2^i` の初期状態区間の集約値」が入っています。

例えば区間和の場合、`leaf()=0` なら `bylen(len, db)=0` です。
区間 min の場合も `bylen(len, db) = e() = INF` になります。
区間和で葉の初期値が `1`（長さ len なら合計 len）のような場合は
`bylen(len, db)` の実装が必要になります。

### `Tag` の要件

通常の `LazySegtree` と同じです。

```cpp
struct Tag{
    using lazy_type=...;
    static value_type Apply(value_type x, lazy_type f);
    static lazy_type Merge(lazy_type old_tag, lazy_type new_tag);
    static lazy_type id();
};
```

## コンストラクタ

### `DynamicLazySegtree(sztype n)`

長さ `n` の領域を作ります（内部で最小の 2 冪に切り上げ）。

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
    static value_type leaf(){ return 0; }
    static value_type bylen(ll len, const vc<value_type>& db){ return 0; }
    // 初期値が 0 なので長さがいくつでも和は 0
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
    static value_type leaf(){ return 1; } // 各要素が初期値 1
    static value_type bylen(ll len, const vc<value_type>& db){
        // 長さ len の初期状態の和 = len
        // db[i] = 2^i (長さ 2^i の区間の和)
        value_type res=0;
        for(int i=0;(1LL<<i)<=len;i++)if(len>>i&1)res+=db[i];
        return res;
    }
};
```

