---
title: 区間演算の定義 | monoid / action
documentation_of: ../../ds/monoid/merger.hpp
keywords: monoid, action, Sum, Prod, Min, Max, merger, affine, lazy_segtree
---

# 区間演算の定義 (`ds/monoid/`, `ds/act/`)

[`segtree`](segtree.md)・[`lazy_segtree`](lazy-segtree.md) などに渡す値の演算と、遅延作用の定義です。用意済みの型で足りない場合は同じ形で自分の `info` / `tag` を定義します。

```cpp
#include "ds/segment_tree/lazy-segtree.hpp"
#include "ds/act/add.hpp"

using A = add_sum<long long>;
lazy_segtree<A> seg(5); // 初期値は 0
seg.apply(1, 4, 3);     // [1,4) に +3
long long ans = seg.prod(0, 5);
```

## 用意されている演算

`ds/monoid/` は `value_type`, `op(a,b)`, `id()` / `e()` を持ちます。`id()` と `e()` は同じ単位元です。

| ヘッダ | 型 | 演算・単位元 |
|---|---|---|
| `sum-prod.hpp` | `Sum<T>`, `Prod<T>` | 加算/0、乗算/1 |
| `min-max.hpp` | `Min<T, INF>`, `Max<T, NEG_INF>` | min/`INF`、max/`NEG_INF` |
| `gcd-lcm.hpp` | `Gcd<T>`, `Lcm<T>` | gcd/0、lcm/1 |
| `bitwise.hpp` | `BitAnd<T>`, `BitOr<T>`, `BitXor<T>` | bit 演算/各単位元 |
| `minmax-count.hpp` | `MinCount<T>`, `MaxCount<T>` | `{値, 個数}`。`make(x)` は `{x,1}` |
| `pair-sum.hpp` | `PairSum<T>` | 2 成分を個別加算 |
| `assign-affine.hpp` | `assign<T>`, `affine<T>` | 代入作用、アフィン写像合成 |
| `merger.hpp` | `merger<I...>` | 複数モノイドを `tuple` にまとめる |
| `reversed.hpp` | `reversed<I>` | `op(a,b)` を `I::op(b,a)` にする |
| `extreme-k.hpp` | `max_k`, `min_k` | 異なる key ごとの上位/下位 K 個 |

`MinCount` / `MaxCount` は値が同じ要素の個数を合算します。`INF` / `NEG_INF` は有効値を越えない番兵値にしてください。`max_k` / `min_k` でも番兵より良い値のみが有効です。

## 遅延作用

`ds/act/` の各型は `info`, `tag`, `value_type`, `lazy_type` と
`act(value, tag, segment_length)` を定義します。`lazy_segtree` / `dual_segtree` に使う型全体をテンプレート引数として渡します。`act` の第 3 引数は区間長で、和の更新など長さに依存する作用に使います。

| ヘッダ | 型 | 作用 |
|---|---|---|
| `add.hpp` | `add_min<T>`, `add_max<T>`, `add_sum<T>` | 区間加算・min/max/sum |
| `assign.hpp` | `assign_min<T>`, `assign_max<T>`, `assign_sum<T>` | 区間代入。タグは `optional<T>` |
| `chmin-chmax.hpp` | `chmin_min/max<T>`, `chmax_min/max<T>` | 各値への `min(x,f)` / `max(x,f)` |
| `mul-affine.hpp` | `mul_sum<T>`, `affine_sum<T>` | 区間乗算 / 区間 affine 変換 |
| `range-linear-range-sum.hpp` | `range_linear_range_sum<T>` | `a[i] += A*i+B` と区間和 |
| `add-extreme-k.hpp` | `add_maxk`, `add_mink` | 上位/下位 K 値すべてに同じ値を加算 |

```cpp
#include "ds/act/assign.hpp"
#include "ds/segment_tree/lazy-segtree.hpp"

using A = assign_sum<long long>;
lazy_segtree<A> seg(8);
seg.apply(2, 6, optional<long long>{5}); // [2,6) を 5 に代入
```

## 性質と注意

- `op` は結合的で、`id()` は左右の単位元である必要があります。可換性は一般の segment tree では不要です。
- `lazy_segtree` では `acted::tag::op(old,new)` が「古い作用の後に新しい作用」を表します。実装の型と順序は [`lazy_segtree`](lazy-segtree.md) を参照してください。
- `affine<T>::op(old, new)` は `new(old(x))` を表します。順序を逆にすると非可換な変換の結果が変わります。
- `assign<T>` は `optional<T>` です。`nullopt` が恒等作用、値ありは代入です。
- `add_sum` / `assign_sum` / `affine_sum` の作用結果は区間長に依存します。各葉を初期化するときの値は、葉長 1 に対する値にしてください。
- すべての演算の時間は `O(1)` です。`merger<I...>` はコンパイル時に指定した個数分を処理します。

## 関連

[segtree](segtree.md) は作用なし、[lazy_segtree](lazy-segtree.md) は値と作用を併用、[dual_segtree](dual-segtree.md) は区間作用と一点取得に向きます。
