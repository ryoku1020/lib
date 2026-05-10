---
title: treap
documentation_of: ../../ds/treap.hpp
---

# treap

implicit treap です。
列として扱い、挿入・削除・区間作用・区間反転・区間積を行えます。

## 型

```cpp
treap<Info, Tag>
```

- `Info` — 値モノイド（省略時: `Noninfo`）
- `Tag` — 遅延作用（省略時: `Nontag`）

`Info` / `Tag` は `LazySegtree` と同じ形式です。

## コンストラクタ

### `treap<Info, Tag>(int max_nodes)`

最大ノード数 `max_nodes` のプールを確保して初期化します。

## メソッド

### `void tr.build(const vc<value_type>& v)`

配列 `v` から treap を構築します。既存の内容はリセットされます。

- 計算量: `O(n)`

### `void tr.insert(int k, value_type v)`

位置 `k` に値 `v` を挿入します（0-indexed、挿入後の位置が `k` になる）。

- 制約: `0 <= k <= size()`
- 計算量: `O(log n)`

### `void tr.erase(int k)`

位置 `k` の要素を削除します（0-indexed）。

- 制約: `0 <= k < size()`
- 計算量: `O(log n)`

### `void tr.apply(int l, int r, lazy_type x)`

区間 `[l, r)` の全要素に作用素 `x` を適用します。

- 制約: `0 <= l <= r <= size()`
- 計算量: `O(log n)`

### `void tr.reverse(int l, int r)`

区間 `[l, r)` を反転します（`Tag` に reverse 用の設定が必要な場合は要対応）。

- 制約: `0 <= l <= r <= size()`
- 計算量: `O(log n)`

### `value_type tr.prod(int l, int r)`

`op(a[l], ..., a[r-1])` を返します。
`l == r` のとき `Info::e()` を返します。

- 制約: `0 <= l <= r <= size()`
- 計算量: `O(log n)`

## 使用例

```cpp
#include "ds/treap.hpp"

// 区間加算・区間和
struct Info{
    using value_type = long long;
    static value_type op(value_type a, value_type b){ return a+b; }
    static value_type e(){ return 0; }
    static value_type leaf(){ return 0; }
};
struct Tag{
    using lazy_type = long long;
    static value_type Apply(value_type x, lazy_type f){ return x+f; }
    static lazy_type Merge(lazy_type a, lazy_type b){ return a+b; }
    static lazy_type id(){ return 0; }
};

treap<Info, Tag> tr(1 << 20);
tr.build(a);          // 配列から構築

tr.insert(pos, x);    // pos に x を挿入
tr.erase(pos);        // pos を削除
tr.apply(l, r, val);  // [l,r) に val を加算
tr.reverse(l, r);     // [l,r) を反転

auto s = tr.prod(l, r); // [l,r) の和
```

## 注意

- `max_nodes` はプールサイズです。`insert` の総回数が超えないよう見積もってください。
- `build` + `insert` を合わせた合計ノード数が `max_nodes` 以下である必要があります。
