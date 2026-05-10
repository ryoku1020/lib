---
title: famous helpers
documentation_of: ../../ds/famous.hpp
---

# famous helpers

`Segtree` / `LazySegtree` / `SparseTable` / `DynamicSegtree` に載せるための代表的な `Info` です。

## 一覧

| 型 | value_type | op | e() | 用途 |
|----|-----------|-----|-----|------|
| `Min<V, inf>` | `V` | `min(a,b)` | `inf` | 区間最小値 |
| `Max<V, neg_inf>` | `V` | `max(a,b)` | `neg_inf` | 区間最大値 |
| `Sum<V>` | `V` | `a+b` | `0` | 区間和 |
| `Prod<V>` | `V` | `a*b` | `1` | 区間積 |
| `Affine<V>` | `pair<V,V>` | affine合成 | `{1,0}` | affine 変換の合成 |
| `Merger<Info...>` | `tuple<...>` | 各 op を並列 | 各 e() | 複数情報の同時管理 |
| `Reversed<Info>` | same | `Info::op(b,a)` | same | 逆順（右から左） |

## 詳細

### `Min<Value_type, inf>`

```cpp
using Info = Min<long long, (long long)4e18>;
```

`inf` は単位元（最大値）。`e() = inf`。

### `Max<Value_type, neg_inf>`

```cpp
using Info = Max<long long, -(long long)4e18>;
```

`neg_inf` は単位元（最小値）。`e() = neg_inf`。

### `Sum<Value_type>`

```cpp
using Info = Sum<long long>; // e() = 0
```

### `Prod<Value_type>`

```cpp
using Info = Prod<long long>; // e() = 1
```

### `Affine<Value_type>`

```cpp
using Info = Affine<long long>;
// value_type = pair<V,V> = {a, b}  → f(x) = ax + b
// op({a1,b1},{a2,b2}) = {a1*a2, b2*a1+b2}（右から左に合成）
```

### `Merger<Info...>`

複数の `Info` を並列に管理します。`value_type` は `tuple`。

```cpp
using Info = Merger<Min<ll,(ll)4e18>, Sum<ll>>;
// value_type = tuple<ll, ll>
// op = (min, sum) を同時に計算
```

### `Reversed<Info>`

`op(a,b)` を `Info::op(b,a)` に変えます。
右端から合成する場合（例: 文字列の右から左への処理）に使います。

## 使用例

```cpp
#include "ds/famous.hpp"

// 区間最小値
Segtree<Min<long long, (long long)4e18>> seg(n);
seg.set(i, v);
auto mn = seg.prod(l, r);

// 区間最大・最小を同時に
using Info = Merger<Max<ll, -(ll)4e18>, Min<ll, (ll)4e18>>;
Segtree<Info> seg2(n);
// value_type = tuple<ll, ll>
auto [mx, mi] = seg2.prod(l, r);
```
