---
title: DynamicSegmentTree
documentation_of: ../../ds/dynamic_segtree.hpp
---

# DynamicSegmentTree

動的セグメント木です。
未生成ノードを省略しながら巨大範囲を扱います。

## 型

### `DynamicSegmentTree<Info, sztype, is_persistent>`

- `is_persistent=true`
  永続版
- `is_persistent=false`
  破壊的更新版

## 主なメソッド

### `Node* seg.build()`

初期 root を返します。

### `Node* seg.set(Node* root, sztype i, value_type x)`

1 点変更後の root を返します。

### `value_type seg.prod(Node* root, int l, int r)`

区間積を返します。

## 注意

- `Info::get2(depth)` が必要です。
