---
title: 区間データ構造追加 | 2D・矩形・列の並べ替え
documentation_of: ../../ds/range_queries/point-add-01.hpp
keywords: pointaddO1, segtree_2d, rectangle_sum, dynamic_rectangle_sum, dynamic_rectangle_add, range_sort_range_product, rangeadd_rangemin
---

# 区間データ構造の追加実装

通常の [`segtree`](segtree.md) や [`wavelet_matrix`](wavelet-matrix.md) と用途が異なる実装をまとめます。座標圧縮が必要な矩形構造は、すべての座標を先に登録して `build()` してから更新・問い合わせを行います。

## 点加算・区間和 (`pointaddO1`)

`pointaddO1<T>` は平方分割で点加算と区間和を行います。

```cpp
#include "ds/range_queries/point-add-01.hpp"

pointaddO1<long long> ds(vector<long long>{1, 2, 3, 4});
ds.add(2, 5);                // a[2] += 5
long long s = ds.query(1, 4); // [1,4) の和 = 14
```

- `pointaddO1<T>(int n)` は 0 初期化、`pointaddO1<T>(const vc<T>& a)` は配列から構築。どちらも `O(n)` 時間・領域。
- `add(i,x)` は `a[i] += x`。`O(1)`。
- `query(l,r)` は `[l,r)` の和を返す。`O(sqrt(n))`。
- 乗法演算ではなく加算可能な `T` が必要です。`build()` はブロック幅・和を再構築します。

## 2D segment tree (`segtree_2d`)

`segtree_2d<info> st(H,W)` は `[0,H) × [0,W)` に点更新し、矩形を集約します。座標は疎にノード確保されます。

```cpp
#include "ds/segment_tree/segtree-2d.hpp"

segtree_2d<Sum<long long>> st(H, W);
st.set(2, 4, 7);                       // (2,4) に 7 を加算
long long s = st.prod(1, 4, 2, 6);      // [1,4) × [2,6) の和
```

- `set(i,j,v)` は名前に反して代入ではなく、葉を `info::op(現在値,v)` に更新します。`O(log H log W)`。
- `prod(L,R,D,U)` は `[L,R) × [D,U)` を `info::op` で集約。空矩形は `info::id()`。`O(log H log W)`。
- `info` は結合的な `op` と単位元 `id()` を持つ必要があります。領域は `O(K log H log W)` 個のノードが目安（K は更新回数）。

## 矩形点集合の和 (`rectangle_sum<T,D>`)

事前登録した重み付き点 `(x,y,w)` に対する矩形和です。

```cpp
#include "ds/range_queries/Rectange.hpp"

rectangle_sum<long long, 32> rs;
rs.add_point(2, 5, 7);
rs.add_point(4, 3, 6);
rs.build();
long long s = rs.query(0, 5, 2, 6); // 0<=x<5, 2<=y<6 の重み和
```

- `add_point(x,y,w)` は点を登録する。全登録の後に `build()` を一度呼ぶ。
- `query(l,r,d,u)` は `l<=x<r` かつ `d<=y<u` の合計。`O(D log n)` を目安とする。
- `D` は y 座標の圧縮順位を格納する wavelet matrix のビット幅。異なる y 座標数を表せるよう十分大きくする。
- 重みは内部で `long long` に一度格納するため、`T` の値は `long long` に正確に収まること。
- `build()` 後の `add_point` はサポートされません。点の重みは `T`、座標は `long long`。

## 動的矩形和・矩形加算（実装要修正）

`dynamic_rectangle_sum<T,D>` は座標を事前登録して構築した後、登録点の重みを変更する設計です。ただし現行実装は `query()` から `wm_base::walk()` を呼びますが、[`wavelet-matrix.hpp`](../../ds/sequence/wavelet-matrix.hpp) にそのメンバがなく、`query()` を使うコードはコンパイルできません。以下はソース上の API 形状であり、現在は利用できません。

この実装は内部に登録座標を複製して保持します。同じ `(x,y)` が重複登録された場合 `add` は lower_bound で最初の一致点だけを更新するため、各座標を一度だけ登録してください。

`dynamic_rectangle_add<T,D>` も `query()` が同じ未定義 `wm_base::walk()` に依存するため、現在は利用できません。設計上は `[l,r)×[d,u)` への加算と原点からの 2D prefix を提供します。

- `add_rec(l,r,d,u,w)` は `build()` 前に四隅を登録し、初期重み `w` を設定します。後の追加更新にも使う全境界を `w=0` で先に登録してください。
- `build()` 後の `add(l,r,d,u,w)` は登録済み四隅へ差分を加算します。新しい座標は登録できません。負の `w` で減算。
- 四隅への符号付きイベントによる 2D 差分です。`query(x,y)` は `[0,x+1) × [0,y+1)` の prefix 値を返します。

## 区間ソートと区間積 (`range_sort_range_product<info,D>`)

列の区間を昇順・降順に並べ替えながら、元の位置に重み付けされた値を置き、区間積を問い合わせます。

```cpp
range_sort_range_product<Sum<long long>, 20> ds(permutation, values);
ds.sort(l, r);        // [l,r) を昇順
ds.rsort(l, r);       // [l,r) を降順
auto total = ds.prod(l, r);
ds.set(i, new_rank, value);
```

コンストラクタの 2 vector は同じ長さで、`permutation[i]` は `[0,2^D)` の順位、`values[i]` はその要素の集約値です。`sort` / `rsort` は状態を破壊的に変更します。`set(i,p,x)` は位置 `i` の順位と値を置き換えます。`prod(l,r)` は `[l,r)` を `info::op` で集約します。`info` は `value_type`, `op`, `e()` を持ちます。順位 trie の高さは `D` ですが、merge 時間は重なる trie node 数に依存し、各範囲操作を単純に `O(log n)` とみなせません。

## 差分列の範囲加算・範囲最小値 (`rangeadd_rangemin<T>`)

元配列の任意区間に値を足し、任意区間の最小値を取ります。内部では差分列を `segtree` で管理します。

- `rangeadd_rangemin<T>(n)` は長さ `n` の 0 初期化列。
- `rangeadd_rangemin<T>(a)` は元配列 `a` を初期化。
- `add(l,r,x)` は `[l,r)` に `x` を加算。`O(log n)`。
- `getmin(l,r)` は `[l,r)` の最小値。`O(log n)`。
- `l==r` の場合、空区間の最小値は定義されず、実装は `inf<T>` を返します。

静的点集合の矩形和は `rectangle_sum`、密な小さい格子には `segtree_2d` を選べます。動的矩形和は上記の実装不備が直るまで選択肢に含めないでください。
