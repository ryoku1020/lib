---
title: PersistentLazySegtree
documentation_of: ../../ds/persistent-lazy-segtree.hpp
---

# PersistentLazySegtree

永続遅延セグメント木です。
各更新が「新しい root インデックス」を返し、過去のバージョンをすべて保持します。

## 要件

`Info` と `Tag` は通常の `LazySegtree` と同様ですが、追加で次が必要です。

### `Info` の追加要件

```cpp
struct Info{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

未生成ノードの値は、`build` で渡した `leaf` から内部で計算されます。

### `Tag` の要件

通常の `LazySegtree` と同じ（`Apply`, `Merge`, `id`）。

## コンストラクタ

### `PersistentLazySegtree()`

初期化するだけで、まだ木は作られていません。

## メソッド

### `int seg.build(int n, value_type leaf = Info::e())`

長さ `n` の初期状態の木を作成し、root インデックスを返します。
未生成ノードを含む各要素の初期値は `leaf` です。
複数回呼ぶことで複数の独立した木を管理できます。

- 計算量: `O(log n)`

### `int seg.set(int i, value_type x, int root)`

`root` バージョンの位置 `i` を `x` に変更した新しい root を返します。
元の `root` はそのまま保持されます。

- 制約: `0<=i<N`
- 計算量: `O(log N)`

### `value_type seg.prod(int l, int r, int root)`

`root` バージョンで `op(a[l],...,a[r-1])` を返します。

- 制約: `0<=l<=r<=N`
- 計算量: `O(log N)`

### `int seg.apply(int l, int r, lazy_type x, int root)`

`root` バージョンの `[l,r)` に作用素 `x` を適用した新しい root を返します。

- 制約: `0<=l<=r<=N`
- 計算量: `O(log N)`

### `int seg.replace(int l, int r, int r1, int r2)`

`r1` バージョンの `[l,r)` を `r2` バージョンの同区間で置き換えた新しい root を返します。
オフライン区間コピー系の問題に使えます。

- 計算量: `O(log N)`

## 境界・注意

- node pool の上限は `MAX_NODE = 1.5e7` でコンパイル時に固定されています。
  クエリ数 $Q$ が多い場合は `O(Q \log N)` ノードを消費するのでオーバーフローに注意。
- 区間は 0-indexed の半開区間 `[l,r)` です。

## 使用例: クエリ時刻ごとの版管理

```cpp
#include "ds/persistent-lazy-segtree.hpp"

// 区間加算・区間最小値 の例
struct Info{
    using value_type = ll;
    static value_type op(value_type a,value_type b){ return min(a,b); }
    static value_type e(){ return (ll)4e18; }
};
struct Tag{
    using lazy_type = ll;
    static value_type Apply(value_type x, lazy_type f){ return x+f; }
    static lazy_type Merge(lazy_type a, lazy_type b){ return a+b; }
    static lazy_type id(){ return 0; }
};

PersistentLazySegtree<Info,Tag> seg;
vc<int> roots;
roots.push_back(seg.build(n)); // バージョン 0

// バージョン t を作成しながら更新
roots.push_back(seg.apply(l, r, x, roots.back())); // バージョン 1

// 過去バージョンへのアクセス
auto ans0 = seg.prod(l, r, roots[0]); // バージョン 0 での結果
auto ans1 = seg.prod(l, r, roots[1]); // バージョン 1 での結果
```
