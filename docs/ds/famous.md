---
title: famous helper | 移行案内
documentation_of: ../../ds/monoid/min-max.hpp
keywords: famous, Min, Max, Sum, Prod, add_sum, assign_sum
---

# `famous` helper の移行案内

旧 `ds/utility/famous.hpp` はこのリポジトリにありません。ここに記載していた型の一部は現在、[monoid と action の定義](algebra.md) に分割されています。

| 以前の名前 | 現在の定義 |
|---|---|
| `Min`, `Max`, `Sum`, `Prod` | `ds/monoid/min-max.hpp`, `sum-prod.hpp` |
| `merger`, `reversed` | `ds/monoid/merger.hpp`, `reversed.hpp` |
| `add_min`, `add_sum`, `assign_sum`, `affine_sum` | `ds/act/*.hpp` |
| `max_k`, `min_k` と `maxk_info`, `mink_info` | `ds/monoid/extreme-k.hpp` |

現行の `lazy_segtree` に作用型を渡すときは、旧形式 `lazy_segtree<Info,Tag>` ではなく `lazy_segtree<acted>` を使います。完全な契約と例は [lazy_segtree](lazy-segtree.md) を参照してください。
