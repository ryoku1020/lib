---
title: PersistentLazySegtree
documentation_of: ../../ds/persistent-lazy-segtree.hpp
---

# PersistentLazySegtree

永続遅延セグメント木です。
更新ごとに新しい root index を返し、過去バージョンを保持します。

## コンストラクタ

### `PersistentLazySegtree()`

## 主なメソッド

### `int seg.build(int n)`

初期 root を返します。

### `int seg.set(int i, value_type x, int root)`

1 点変更した新 root を返します。

### `value_type seg.prod(int l, int r, int root)`

指定バージョンでの区間積です。

### `int seg.apply(int l, int r, lazy_type x, int root)`

区間作用後の新 root を返します。

### `int seg.replace(int l, int r, int r1, int r2)`

`r1` の `[l,r)` を `r2` の同区間で置き換えた新 root を返します。

## 注意

- `Info::bylen` を要求します。
- 大きい固定 node pool を使っています。
