# コードベース ドキュメント

各ファイルおよび構造体の計算量と副作用のドキュメントです。

## fast_io.hpp

### FastWrite

#### 概要
`FastWrite` データ構造。

#### 使い方
- `FastWrite(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `skip_space(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `read(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `fread(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `copy_n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `parse(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### FastRead

#### 概要
`FastRead` データ構造。

#### 使い方
- `FastRead(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `skip_space(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `read(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `fread(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `copy_n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `parse(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## monge.hpp

#### 概要
汎用関数群。計算量や副作用は呼び出し元に依存します。

## t.hpp

#### 概要
汎用関数群。計算量や副作用は呼び出し元に依存します。

## ds/AssignSegmentTree.hpp

### AssignSegmentTree

#### 概要
`AssignSegmentTree` データ構造。

#### 使い方
- `AssignSegmentTree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `decltype(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `constexpr(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Info

#### 概要
`Info` データ構造。

#### 使い方
- `Info(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `decltype(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `constexpr(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/BinaryIndexedTree.hpp

### BinaryIndexedTree

#### 概要
`BinaryIndexedTree` データ構造。

#### 使い方
- `BinaryIndexedTree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `data(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `internal_sum(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `sum(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/ConvexHullTrick.hpp

### ConvexHullTrick

#### 概要
`ConvexHullTrick` データ構造。

#### 使い方
- `ConvexHullTrick(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `eval(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `rep(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `back(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add_line(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/DoublePriorityQueue.hpp

### DoublePriorityQueue

#### 概要
`DoublePriorityQueue` データ構造。

#### 使い方
- `DoublePriorityQueue(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `push(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `remove(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `pop(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `modify(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `top(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/DynamicLazySegmentTree.hpp

### DynamicLazySegmentTree

#### 概要
`DynamicLazySegmentTree` データ構造。

#### 使い方
- `DynamicLazySegmentTree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `lazy(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Tag

#### 概要
`Tag` データ構造。

#### 使い方
- `Tag(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `lazy(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Info

#### 概要
`Info` データ構造。

#### 使い方
- `Info(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `lazy(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### sztype

#### 概要
`sztype` データ構造。

#### 使い方
- `sztype(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `lazy(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/DynamicSegmentTree.hpp

### DynamicSegmentTree

#### 概要
`DynamicSegmentTree` データ構造。

#### 使い方
- `DynamicSegmentTree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `r(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `new_node(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Info

#### 概要
`Info` データ構造。

#### 使い方
- `Info(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `r(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `new_node(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### sztype

#### 概要
`sztype` データ構造。

#### 使い方
- `sztype(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `r(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `new_node(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/Hash.hpp

### Roll

#### 概要
`Roll` データ構造。

#### 使い方
- `Roll(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `get(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `un(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `init(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `seed(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/LazySegmentTree.hpp

### Tag

#### 概要
`Tag` データ構造。

#### 使い方
- `Tag(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `decltype(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `constexpr(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### lazy_segtree

#### 概要
`lazy_segtree` データ構造。

#### 使い方
- `lazy_segtree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `decltype(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `constexpr(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Info

#### 概要
`Info` データ構造。

#### 使い方
- `Info(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `decltype(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `constexpr(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/Mo.hpp

#### 概要
汎用関数群。計算量や副作用は呼び出し元に依存します。

## ds/PersistentLazySegmentTree.hpp

### PersistentLazySegmentTree

#### 概要
`PersistentLazySegmentTree` データ構造。

#### 使い方
- `PersistentLazySegmentTree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `lazy(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Tag

#### 概要
`Tag` データ構造。

#### 使い方
- `Tag(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `lazy(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Info

#### 概要
`Info` データ構造。

#### 使い方
- `Info(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `lazy(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/PersistentUnionFind.hpp

### PersistentUnionFind

#### 概要
`PersistentUnionFind` データ構造。

#### 使い方
- `PersistentUnionFind(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `root(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `get(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `same(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `merge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/PotentialUnionFind.hpp

### PotentialUnionFind

#### 概要
`PotentialUnionFind` データ構造。

#### 使い方
- `PotentialUnionFind(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `par(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `w(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `root(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/RangeUnionFind.hpp

### DisjointSetUnion

#### 概要
`DisjointSetUnion` データ構造。

#### 使い方
- `DisjointSetUnion(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `par(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `w(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `ans(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `set(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `root(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### SuperDisjointSetUnion

#### 概要
`SuperDisjointSetUnion` データ構造。

#### 使い方
- `SuperDisjointSetUnion(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `par(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `w(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `ans(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `set(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `root(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/Reroot.hpp

### Reroot

#### 概要
`Reroot` データ構造。

#### 使い方
- `Reroot(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `merge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `put_vertex(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `put_edge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `g(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Redp

#### 概要
`Redp` データ構造。

#### 使い方
- `Redp(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `merge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `put_vertex(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `put_edge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `g(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/SegmentTree.hpp

### segtree

#### 概要
`segtree` データ構造。

#### 使い方
- `segtree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `update(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `segtree(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/SuperDisjointSetUnion.hpp

### SuperDisjointSetUnion

#### 概要
`SuperDisjointSetUnion` データ構造。

#### 使い方
- `SuperDisjointSetUnion(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `rep(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `root(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `merge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `same(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/UndoUnionFind.hpp

### UndoUnionFind

#### 概要
`UndoUnionFind` データ構造。

#### 使い方
- `UndoUnionFind(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `root(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `same(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `merge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `push(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `save(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/UnionFind.hpp

### base_dsu

#### 概要
`base_dsu` データ構造。

#### 使い方
- `base_dsu(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `base_dsu(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `par(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `static_assert(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `data(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leader(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/compress.hpp

### compress

#### 概要
`compress` データ構造。

#### 使い方
- `compress(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `compress(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `reserve(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `push(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `co(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `sort(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/dual.hpp

### DualSegmentTree

#### 概要
`DualSegmentTree` データ構造。

#### 使い方
- `DualSegmentTree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `rep(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `set(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `push(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/famous.hpp

### Reversed

#### 概要
`Reversed` データ構造。

#### 使い方
- `Reversed(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Sum

#### 概要
`Sum` データ構造。

#### 使い方
- `Sum(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Affine

#### 概要
`Affine` データ構造。

#### 使い方
- `Affine(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Max

#### 概要
`Max` データ構造。

#### 使い方
- `Max(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Value_type

#### 概要
`Value_type` データ構造。

#### 使い方
- `Value_type(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Prod

#### 概要
`Prod` データ構造。

#### 使い方
- `Prod(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### ArgMin

#### 概要
`ArgMin` データ構造。

#### 使い方
- `ArgMin(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Min

#### 概要
`Min` データ構造。

#### 使い方
- `Min(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### Info

#### 概要
`Info` データ構造。

#### 使い方
- `Info(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### ArgMax

#### 概要
`ArgMax` データ構造。

#### 使い方
- `ArgMax(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `leaf(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/fastset.hpp

### fastset

#### 概要
`fastset` データ構造。

#### 使い方
- `fastset(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `fastset(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `raw(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `pb(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `dig(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `rep(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/persisitent_array.hpp

### persisitent_array

#### 概要
`persisitent_array` データ構造。

#### 使い方
- `persisitent_array(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `fill(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `rep(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `dfs(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/re_union.hpp

### Rec

#### 概要
`Rec` データ構造。

#### 使い方
- `Rec(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `reserve(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `ap(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### reunion

#### 概要
`reunion` データ構造。

#### 使い方
- `reunion(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `id(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `reserve(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `ap(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/sparse_table.hpp

### sparse_table

#### 概要
`sparse_table` データ構造。

#### 使い方
- `sparse_table(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `sparse_table(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `set(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `rep(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## ds/swag.hpp

### SWAG

#### 概要
`SWAG` データ構造。

#### 使い方
- `SWAG(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `push_front(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `back(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `balance(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### oneway_swag

#### 概要
`oneway_swag` データ構造。

#### 使い方
- `oneway_swag(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `e(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `push_front(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `op(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `back(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `balance(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## graph/BipartiteMatching.hpp

### BipartiteMatching

#### 概要
`BipartiteMatching` データ構造。

#### 使い方
- `BipartiteMatching(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `l(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `r(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `pm(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `qm(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `g(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## graph/CompressedSparseRow.hpp

### CompressedSparseRowGraph

#### 概要
`CompressedSparseRowGraph` データ構造。

#### 使い方
- `CompressedSparseRowGraph(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `begin(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `end(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `row_ptr(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add_edge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### RowView

#### 概要
`RowView` データ構造。

#### 使い方
- `RowView(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `begin(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `end(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `row_ptr(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add_edge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## graph/StronglyConnectedComponents.hpp

### StronglyConnectedComponents

#### 概要
`StronglyConnectedComponents` データ構造。

#### 使い方
- `StronglyConnectedComponents(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `g(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `inv(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add_edge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## graph/TwoSatisfiability.hpp

### TwoSatisfiability

#### 概要
`TwoSatisfiability` データ構造。

#### 使い方
- `TwoSatisfiability(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `sc(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `ans(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add_clause(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## graph/flow.hpp

### edge

#### 概要
`edge` データ構造。

#### 使い方
- `edge(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `g(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add_edge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `bfs(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `push(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### MaximumFlow

#### 概要
`MaximumFlow` データ構造。

#### 使い方
- `MaximumFlow(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `g(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `add_edge(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `bfs(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `push(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/Convolution.hpp

### fft_info

#### 概要
`fft_info` データ構造。

#### 使い方
- `fft_info(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `safe_mod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `barrett(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `_m(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `im(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `umod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### barrett

#### 概要
`barrett` データ構造。

#### 使い方
- `barrett(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `safe_mod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `barrett(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `_m(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `im(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `umod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### mint

#### 概要
`mint` データ構造。

#### 使い方
- `mint(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `safe_mod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `barrett(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `_m(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `im(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `umod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/DynamicModInt.hpp

### DynamicModInt

#### 概要
`DynamicModInt` データ構造。

#### 使い方
- `DynamicModInt(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `get_mod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `raw(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `rem(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `u64(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/FormalPowerSeries.hpp

### subproduct_tree

#### 概要
`subproduct_tree` データ構造。

#### 使い方
- `subproduct_tree(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `begin(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `end(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `inv(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `poly(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `np(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### FormalPowerSeries

#### 概要
`FormalPowerSeries` データ構造。

#### 使い方
- `FormalPowerSeries(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `begin(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `end(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `inv(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `poly(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `np(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### mint

#### 概要
`mint` データ構造。

#### 使い方
- `mint(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `begin(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `end(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `inv(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `poly(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `np(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/Matrix.hpp

### Matrix

#### 概要
`Matrix` データ構造。

#### 使い方
- `Matrix(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `decltype(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `get_mod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `a(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `m(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### is_mint

#### 概要
`is_mint` データ構造。

#### 使い方
- `is_mint(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `decltype(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `get_mod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `a(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `m(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/ModularArithmetic.hpp

### Binom

#### 概要
`Binom` データ構造。

#### 使い方
- `Binom(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `mint(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `back(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `inv(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `extgcd(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

### mint

#### 概要
`mint` データ構造。

#### 使い方
- `mint(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `build(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `mint(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `back(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `inv(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `extgcd(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/StaticModInt.hpp

### StaticModInt

#### 概要
`StaticModInt` データ構造。

#### 使い方
- `StaticModInt(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `get_mod(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `raw(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `u64(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `inv(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/barrett.hpp

### Barrett

#### 概要
`Barrett` データ構造。

#### 使い方
- `Barrett(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `set(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `i128(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `reduce(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/bostan_mori.hpp

### mint

#### 概要
`mint` データ構造。

#### 使い方
- `mint(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `bostan_mori(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `bp(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `bq(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `np_full(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `nq_half(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## math/mod261.hpp

### mod261

#### 概要
`mod261` データ構造。

#### 使い方
- `mod261(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `rem(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `mod261(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `val(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `raw(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `inv(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。

## other/commute_cheker.hpp

#### 概要
汎用関数群。計算量や副作用は呼び出し元に依存します。

## string/LongestCommonPrefixSuffix.hpp

#### 概要
汎用関数群。計算量や副作用は呼び出し元に依存します。

## tree/HeavyLightDecomposition.hpp

### HeavyLightDecomposition

#### 概要
`HeavyLightDecomposition` データ構造。

#### 使い方
- `HeavyLightDecomposition(...)`: コンストラクタ。内部状態の初期化を行います。計算量 $\mathrm{O(N)}$ または $\mathrm{O(1)}$
- `n(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `gfirst(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `g(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `head(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
- `in(...)`: 操作を実行します。計算量 $\mathrm{O(\log N)}$ または $\mathrm{O(1)}$ または $\mathrm{O(N)}$、副作用: 内部状態を更新する場合があります。
