---
title: 動的遅延セグメント木 | dynamic_lazy_segtree
documentation_of: ../../ds/segment_tree/dynamic-lazy-segtree.hpp
keywords: 巨大座標, 区間更新, 区間和, dynamic_lazy_segtree
---

# 動的遅延セグメント木 (`dynamic_lazy_segtree`)

巨大な整数範囲を必要なノードだけ生成して扱う遅延セグメント木です。座標範囲 `[0,n)` を宣言し、区間更新・区間集約を行います。通常サイズなら [`lazy_segtree`](lazy-segtree.md) の方が簡潔です。

```cpp
#include "ds/act/add.hpp"
#include "ds/segment_tree/dynamic-lazy-segtree.hpp"

using ll = long long;
using A = add_sum<ll>;
dynamic_lazy_segtree<A,ll> seg((ll)1e18, 0LL);
seg.apply(10, 20, 3LL);       // [10,20) を +3
ll sum = seg.prod(0, 100);    // 30
```

## 型と構築

テンプレートは `dynamic_lazy_segtree<acted,sztype=int>`。`acted` は `lazy_segtree` と同様、`info`, `tag`, `value_type`, `lazy_type`, `act(value,tag,length)` をまとめた型です。

- `info::op(a,b)` は結合的、`info::id()` は単位元。
- `tag::op(old,new)` は新しい作用を古い作用の後に適用した合成。`tag::id()` は恒等作用。
- `acted::act(value,f,length)` は集約値に作用。区間和なら区間長が必要です。
- `tag::commute=true` は作用タグが可換の場合のみ。省略時は `false`。
- `dynamic_lazy_segtree<acted,sztype>(n, leaf=info::id())` は長さ `n`、葉初期値 `leaf` で構築。高さ・初期集約表を作るため `O(log n)` 時間・領域、各操作が必要なノードを確保します。`n>=0`。

`n` は座標の上限（排他的）です。内部では `n` 以上の最小 2 冪に切り上げます。`sztype` は `int` または十分な幅の符号付き整数型を指定します。

## 操作

| 呼び出し | 動作・返り値 | 計算量 |
|---|---|---|
| `seg.set(i,x)` | `a[i]=x` に上書き | `O(log n)` |
| `seg.prod(l,r)` | `[l,r)` の `info::op` 集約値。空区間は `info::id()` | `O(log n)` |
| `seg.apply(l,r,f)` | `[l,r)` へ作用 `f` を適用 | `O(log n)` |

すべて 0-indexed 半開区間。`0<=i<n`, `0<=l<=r<=n` を守ります。

## メモリ・注意

- 1 操作あたり `O(log n)` 個を上限とする新規ノードが必要になるため、`q` 回の更新に `O(q log n)` 領域が目安です。上限固定の node pool はなく、メモリは利用可能領域に依存します。
- node pool はインスタンスごとに持つため、同じ型の複数の木を同時に使えます。
- 実装上の assert は切り上げ後の 2 冪サイズまで許す箇所がありますが、必ず論理範囲 `[0,n)` 内で操作します。
- `leaf` は各要素の値です。区間集約値ではありません。例えば和なら値 `0`、作用時の長さは内部で管理されます。
- 合成順・作用条件の詳細は [`lazy_segtree`](lazy-segtree.md) と [monoid/action](algebra.md) を参照。
