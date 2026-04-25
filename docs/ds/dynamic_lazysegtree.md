---
title: DynamicLazySegmentTree
documentation_of: ../../ds/dynamic_lazysegtree.hpp
---

# DynamicLazySegmentTree

動的遅延セグメント木です。
巨大座標範囲を暗黙木で扱います。

## コンストラクタ

### `DynamicLazySegmentTree(sztype n)`

長さ `n` の領域を作ります。

## 主なメソッド

### `void seg.set(sztype i, value_type x)`
### `value_type seg.prod(sztype l, sztype r)`
### `void seg.apply(sztype l, sztype r, lazy_type x)`

## 注意

- `Info::bylen` と `Info::leaf` が必要です。
- node pool の上限があります。
