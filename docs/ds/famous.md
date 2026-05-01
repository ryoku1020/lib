---
title: famous helpers
documentation_of: ../../ds/famous.hpp
---

# famous helpers

汎用データ構造に載せるための代表的な `Info` たちです。

## 含まれるもの

- `Min<Value_type, inf>`
- `Max<Value_type, neg_inf>`
- `Sum<Value_type>`
- `Prod<Value_type>`
- `Merger<Infos...>`
- `Affine<Value_type>`
- `Reversed<Info>`

## 用途

- `Segtree`
- `LazySegtree`
- `SparseTable`
- `DynamicSegtree`

## 例

```cpp
using Info=Min<long long,(long long)4e18>;
Segtree<Info> seg(n);
```
