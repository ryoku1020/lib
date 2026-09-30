---
title: dual segment tree | dual_segtree
documentation_of: ../../ds/segment_tree/dual-segtree.hpp
keywords: 区間更新, 一点取得, dual_segtree, apply, get
---

# dual segment tree (`dual_segtree`)

区間に作用を適用して一点取得します。区間集約が要る場合は [`lazy_segtree`](lazy-segtree.md) を使います。

```cpp
#include "ds/segment_tree/dual-segtree.hpp"
#include "ds/act/add.hpp"

using A = add_sum<long long>;
dual_segtree<A> seg(5);
seg.apply(1, 4, 3);       // [1,4) に +3
long long x = seg.get(2); // 3
```

## 要件

テンプレートは `dual_segtree<acted>` です。`acted` は [`lazy_segtree`](lazy-segtree.md) と同様に `info`, `tag`, `value_type`, `lazy_type`, `act(value,tag,length)` を定義します。ここでは葉への作用時の長さは常に 1 です。pending tag は `tag::op(old,new)` で合成されます。`tag::commute=true` は任意で、タグ同士が可換な場合のみ指定します。

## コンストラクタ・操作

- `dual_segtree<acted>(n)` は `n` 点を `info::id()` 相当の値で初期化。`O(n)`。
- `dual_segtree<acted>(n, values)` は `values` で初期化。`values.size()<=2^ceil(log2(n))` が必要。
- `build(values)` は葉を初期化します。コンストラクタ後に呼ぶ場合、`values.size()<=2^ceil(log2(n))`。
- `set(p,x,is_first=false)` は位置 `p` を `x` にする。通常の `false` では先行する作用を伝播してから上書き。`is_first=true` は pending tag のない構築時にのみ使う低レベル設定で、葉の index が論理範囲 `[0,n)` 内であることを呼び出し側が確認する。
- `apply(l,r,x)` は `[l,r)` に作用 `x` を積む。空区間は何もしない。`O(log n)`。
- `get(p)` は位置 `p` の現在値を返す。`O(log n)`。

## 注意

- 区間は 0-indexed 半開区間 `[l,r)`。
- この実装に range product はありません。
- 内部サイズは `n` 以上の最小の 2 冪 `n` です。実装の境界 assert は padded 領域まで許すため、API の呼び出しは論理範囲 `[0,n)` に留めます。
- `commute=true` のとき `get` は pending tag を合成して返し、push しません。作用合成・値作用の前提を満たしてください。

## 使用例: 区間代入・一点取得

```cpp
#include "ds/segment_tree/dual-segtree.hpp"
#include "ds/act/assign.hpp"

using A = assign_sum<int>;
dual_segtree<A> seg(6);
seg.apply(1, 5, optional<int>{7});
int x = seg.get(3); // 7
```
