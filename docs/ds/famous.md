---
title: famous helpers
documentation_of: ../../ds/famous.hpp
---

# famous helpers

`Segtree` / `LazySegtree` / `SparseTable` / `DynamicSegtree` に載せるための代表的な `Info` と補助データ型です。

## 一覧

| 型 | value_type | op | e() | 用途 |
|----|-----------|-----|-----|------|
| `Min<V, inf>` | `V` | `min(a,b)` | `inf` | 区間最小値 |
| `Max<V, neg_inf>` | `V` | `max(a,b)` | `neg_inf` | 区間最大値 |
| `Sum<V>` | `V` | `a+b` | `0` | 区間和 |
| `Prod<V>` | `V` | `a*b` | `1` | 区間積 |
| `Affine<V>` | `pair<V,V>` | affine合成 | `{1,0}` | affine 変換の合成 |
| `AddMin<V>` | nested | - | - | 区間加算・区間最小値 |
| `AddMax<V>` | nested | - | - | 区間加算・区間最大値 |
| `AddSum<V>` | nested | - | - | 区間加算・区間和 |
| `AssignMin<V>` | nested | - | - | 区間代入・区間最小値 |
| `AssignMax<V>` | nested | - | - | 区間代入・区間最大値 |
| `AssignSum<V>` | nested | - | - | 区間代入・区間和 |
| `AffineSum<V>` | nested | - | - | 区間 affine・区間和 |
| `Merger<Info...>` | `tuple<...>` | 各 op を並列 | 各 e() | 複数情報の同時管理 |
| `Reversed<Info>` | same | `Info::op(b,a)` | same | 逆順（右から左） |
| `MaxK<Key,Val,K,neg_inf>` | - | - | - | key ごとの上位 K 個 |
| `MinK<Key,Val,K,inf>` | - | - | - | key ごとの下位 K 個 |
| `MaxKInfo<Key,Val,K,neg_inf>` | `MaxK<Key,Val,K,neg_inf>` | merge | 空 | `MaxK` をセグ木等に載せる |
| `MinKInfo<Key,Val,K,inf>` | `MinK<Key,Val,K,inf>` | merge | 空 | `MinK` をセグ木等に載せる |

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

### `AddMin<Value_type>` / `AddMax<Value_type>` / `AddSum<Value_type>`

`LazySegtree` 用に `Info` と `Tag` をまとめた型です。

```cpp
using X = AddSum<ll>;
LazySegtree<X::Info, X::Tag> seg(n, a);
seg.apply(l, r, x);
auto ans = seg.prod(l, r).first;
```

`AddSum<V>::Info::value_type` は `{sum,len}` です。

### `AssignMin<Value_type>` / `AssignMax<Value_type>` / `AssignSum<Value_type>`

区間代入用です。`Tag` は `{true,value}` で代入、`{false,0}` で恒等作用です。

```cpp
using X = AssignSum<ll>;
LazySegtree<X::Info, X::Tag> seg(n, a);
seg.apply(l, r, {true, x});
auto ans = seg.prod(l, r).first;
```

`AssignSum<V>::Info::value_type` は `{sum,len}` です。

### `AffineSum<Value_type>`

区間 affine 変換・区間和です。`Tag` は `{a,b}` で `x -> a*x+b` を表します。

```cpp
using X = AffineSum<mint>;
LazySegtree<X::Info, X::Tag> seg(n, a);
seg.apply(l, r, {a, b});
auto ans = seg.prod(l, r).first;
```

`AffineSum<V>::Info::value_type` は `{sum,len}` です。

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

### `MaxK<Key,Val,K,neg_inf>` / `MinK<Key,Val,K,inf>`

`MaxK` は key が重複しないように value の大きい順で K 個、`MinK` は小さい順で K 個持ちます。
`add_element(key,val)` は追加・更新できたら `1`、できなかったら `0` を返します。
`has(key,val)` は現在保持している有効な要素に一致するものがあれば `true` を返します。

```cpp
MaxK<ll,ll,2,-inf<ll>> x;
x.add_element(3, 10); // 1
x.add_element(4, 7);  // 1
x.add_element(5, 5);  // 0
bool ok = x.has(3, 10);
auto best = x[0];

using Y = MinK<ll,pll,2,pll{inf<ll>,inf<ll>}>;
```

セグ木などの `Info` として使う場合は `MaxKInfo` / `MinKInfo` を使います。

```cpp
using Info = MaxKInfo<ll,ll,2,-inf<ll>>;
Segtree<Info> seg(n);
MaxK<ll,ll,2,-inf<ll>> x;
x.add_element(3, 10);
seg.set(i, x);
```

## 境界・注意

- ここにある型は、主に `Info` として他のデータ構造に渡すための部品です。
- `Min` / `Max` の `inf` / `neg_inf` は問題の値域より十分外側の値を指定してください。
- `Merger` は複数の情報を同じ区間で同時に持つための型です。片方だけ更新するような用途には向きません。

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
