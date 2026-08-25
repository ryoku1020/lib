---
title: famous helpers
documentation_of: ../../ds/utility/famous.hpp
---

# famous helpers

`segtree` / `lazy_segtree` / `sparse_table` / `dynamic_segtree` に載せるための代表的な `info` と補助データ型です。

## 一覧

| 型 | value_type | op | e() | 用途 |
|----|-----------|-----|-----|------|
| `Min<V, inf>` | `V` | `min(a,b)` | `inf` | 区間最小値 |
| `Max<V, neg_inf>` | `V` | `max(a,b)` | `neg_inf` | 区間最大値 |
| `Sum<V>` | `V` | `a+b` | `0` | 区間和 |
| `Prod<V>` | `V` | `a*b` | `1` | 区間積 |
| `affine<V>` | `pair<V,V>` | affine合成 | `{1,0}` | affine 変換の合成 |
| `add_min<V>` | nested | - | - | 区間加算・区間最小値 |
| `add_max<V>` | nested | - | - | 区間加算・区間最大値 |
| `add_sum<V>` | nested | - | - | 区間加算・区間和 |
| `assign_min<V>` | nested | - | - | 区間代入・区間最小値 |
| `assign_max<V>` | nested | - | - | 区間代入・区間最大値 |
| `assign_sum<V>` | nested | - | - | 区間代入・区間和 |
| `affine_sum<V>` | nested | - | - | 区間 affine・区間和 |
| `merger<info...>` | `tuple<...>` | 各 op を並列 | 各 e() | 複数情報の同時管理 |
| `reversed<info>` | same | `info::op(b,a)` | same | 逆順（右から左） |
| `max_k<Key,Val,K,neg_inf>` | - | - | - | key ごとの上位 K 個 |
| `min_k<Key,Val,K,inf>` | - | - | - | key ごとの下位 K 個 |
| `maxk_info<Key,Val,K,neg_inf>` | `max_k<Key,Val,K,neg_inf>` | merge | 空 | `max_k` をセグ木等に載せる |
| `mink_info<Key,Val,K,inf>` | `min_k<Key,Val,K,inf>` | merge | 空 | `min_k` をセグ木等に載せる |

## 詳細

### `Min<Value_type, inf>`

```cpp
using info = Min<long long, (long long)4e18>;
```

`inf` は単位元（最大値）。`e() = inf`。

### `Max<Value_type, neg_inf>`

```cpp
using info = Max<long long, -(long long)4e18>;
```

`neg_inf` は単位元（最小値）。`e() = neg_inf`。

### `Sum<Value_type>`

```cpp
using info = Sum<long long>; // e() = 0
```

### `Prod<Value_type>`

```cpp
using info = Prod<long long>; // e() = 1
```

### `affine<Value_type>`

```cpp
using info = affine<long long>;
// value_type = pair<V,V> = {a, b}  → f(x) = ax + b
// op({a1,b1},{a2,b2}) = {a1*a2, b2*a1+b2}（右から左に合成）
```

### `add_min<Value_type>` / `add_max<Value_type>` / `add_sum<Value_type>`

`lazy_segtree` 用に `info` と `tag` をまとめた型です。

```cpp
using X = add_sum<ll>;
lazy_segtree<X::info, X::tag> seg(n, a);
seg.apply(l, r, x);
auto ans = seg.prod(l, r).first;
```

`add_sum<V>::info::value_type` は `{sum,len}` です。
`add_min` / `add_max` / `add_sum` のタグは可換なので、`tag::commute=true` が設定されています。
`Min` / `Max` / `Sum` / `Prod` と、これらを組み合わせた可換な `merger` には `info::commute=true` が設定されています。

### `assign_min<Value_type>` / `assign_max<Value_type>` / `assign_sum<Value_type>`

区間代入用です。`tag` は `{true,value}` で代入、`{false,0}` で恒等作用です。

```cpp
using X = assign_sum<ll>;
lazy_segtree<X::info, X::tag> seg(n, a);
seg.apply(l, r, {true, x});
auto ans = seg.prod(l, r).first;
```

`assign_sum<V>::info::value_type` は `{sum,len}` です。

### `affine_sum<Value_type>`

区間 affine 変換・区間和です。`tag` は `{a,b}` で `x -> a*x+b` を表します。

```cpp
using X = affine_sum<mint>;
lazy_segtree<X::info, X::tag> seg(n, a);
seg.apply(l, r, {a, b});
auto ans = seg.prod(l, r).first;
```

`affine_sum<V>::info::value_type` は `{sum,len}` です。

### `merger<info...>`

複数の `info` を並列に管理します。`value_type` は `tuple`。

```cpp
using info = merger<Min<ll,(ll)4e18>, Sum<ll>>;
// value_type = tuple<ll, ll>
// op = (min, sum) を同時に計算
```

### `reversed<info>`

`op(a,b)` を `info::op(b,a)` に変えます。
右端から合成する場合（例: 文字列の右から左への処理）に使います。

### `max_k<Key,Val,K,neg_inf>` / `min_k<Key,Val,K,inf>`

`max_k` は key が重複しないように value の大きい順で K 個、`min_k` は小さい順で K 個持ちます。
`add_element(key,val)` は追加・更新できたら `1`、できなかったら `0` を返します。
`has(key,val)` は現在保持している有効な要素に一致するものがあれば `true` を返します。

```cpp
max_k<ll,ll,2,-inf<ll>> x;
x.add_element(3, 10); // 1
x.add_element(4, 7);  // 1
x.add_element(5, 5);  // 0
bool ok = x.has(3, 10);
auto best = x[0];

using Y = min_k<ll,pll,2,pll{inf<ll>,inf<ll>}>;
```

セグ木などの `info` として使う場合は `maxk_info` / `mink_info` を使います。

```cpp
using info = maxk_info<ll,ll,2,-inf<ll>>;
segtree<info> seg(n);
max_k<ll,ll,2,-inf<ll>> x;
x.add_element(3, 10);
seg.set(i, x);
```

## 境界・注意

- ここにある型は、主に `info` として他のデータ構造に渡すための部品です。
- `Min` / `Max` の `inf` / `neg_inf` は問題の値域より十分外側の値を指定してください。
- `merger` は複数の情報を同じ区間で同時に持つための型です。片方だけ更新するような用途には向きません。

## 使用例

```cpp
#include "ds/utility/famous.hpp"

// 区間最小値
segtree<Min<long long, (long long)4e18>> seg(n);
seg.set(i, v);
auto mn = seg.prod(l, r);

// 区間最大・最小を同時に
using info = merger<Max<ll, -(ll)4e18>, Min<ll, (ll)4e18>>;
segtree<info> seg2(n);
// value_type = tuple<ll, ll>
auto [mx, mi] = seg2.prod(l, r);
```
