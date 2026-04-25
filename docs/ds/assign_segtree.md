---
title: AssignSegmentTree
documentation_of: ../../ds/assign_segtree.hpp
---

# AssignSegmentTree

区間代入と区間積取得を行うセグメント木です。

## 要件

`Info` に `value_type`, `op`, `e`、必要なら `leaf` を定義します。

## コンストラクタ

### `AssignSegmentTree(int n)`

長さ `n` で初期化します。

## メソッド

### `void seg.assign(int l, int r, value_type x)`

区間 `[l,r)` をすべて `x` に代入します。

### `value_type seg.prod(int l, int r)`

区間積を返します。

### `void seg.set(int i, value_type x)`

1 点代入です。

### `void seg.reset()`

内部にたまった代入テーブルを整理してリセットします。

## 注意

- 区間代入専用です。一般遅延作用ではありません。
