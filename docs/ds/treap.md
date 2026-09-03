---
title: treap
documentation_of: ../../ds/ordered/treap.hpp
---

# treap

implicit treap です。
列として扱い、挿入・削除・区間作用・区間反転・区間積を行えます。

## 型

```cpp
treap<info, tag>
```

- `info` — 値モノイド（省略時: `noninfo`）
- `tag` — 遅延作用（省略時: `nontag`）

`info` / `tag` は `lazy_segtree` と同じ形式です。

## コンストラクタ

### `treap<info, tag>(int max_nodes)`

最大ノード数 `max_nodes` のプールを確保して初期化します。

- 制約: `max_nodes>0`
- 計算量: `O(max_nodes)` の領域を確保

## メソッド

### `void tr.build(const vc<value_type>& v)`

配列 `v` から treap を構築します。既存の内容はリセットされます。

- 計算量: `O(n)`

### `void tr.insert(int k, value_type v)`

位置 `k` に値 `v` を挿入します（0-indexed、挿入後の位置が `k` になる）。

- 制約: `0 <= k <= size()`
- 計算量: 期待 `O(log n)`

### `void tr.erase(int k)`

位置 `k` の要素を削除します（0-indexed）。

- 制約: `0 <= k < size()`
- 計算量: 期待 `O(log n)`

### `void tr.apply(int l, int r, lazy_type x)`

区間 `[l, r)` の全要素に作用素 `x` を適用します。

- 制約: `0 <= l <= r <= size()`
- 計算量: 期待 `O(log n)`

### `void tr.reverse(int l, int r)`

区間 `[l, r)` を反転します。非可換な `info::op` に対しても、内部の逆順集約値を使って処理します。

- 制約: `0 <= l <= r <= size()`
- 計算量: 期待 `O(log n)`

### `value_type tr.prod(int l, int r)`

`op(a[l], ..., a[r-1])` を返します。
`l == r` のとき `info::e()` を返します。

- 制約: `0 <= l <= r <= size()`
- 計算量: 期待 `O(log n)`

## 境界・注意

- `max_nodes` はプールサイズです。`insert` の総回数が超えないよう見積もってください。
- `build` + `insert` を合わせた合計ノード数が `max_nodes` 以下である必要があります。
- `erase` したノードは pool に戻りません。また `build` を再度呼ぶと列の root は置き換わりますが、以前のノード領域は再利用されません。
- 木の高さは乱択に依存するため、各操作の `O(log n)` は期待計算量です。

## 使用例

```cpp
#include "ds/ordered/treap.hpp"

// 区間加算・区間和
struct info{
    using value_type = pair<long long,int>; // {sum,len}
    static value_type op(value_type a, value_type b){
        return {a.first+b.first,a.second+b.second};
    }
    static value_type e(){ return {0,0}; }
};
struct tag{
    using lazy_type = long long;
    static info::value_type apply(info::value_type x, lazy_type f){
        return {x.first+(long long)x.second*f,x.second};
    }
    static lazy_type merge(lazy_type a, lazy_type b){ return a+b; }
    static lazy_type id(){ return 0; }
};

treap<info, tag> tr(1 << 20);
vc<info::value_type> init(n);
for(int i=0;i<n;i++)init[i]={a[i],1};
tr.build(init);       // 配列から構築

tr.insert(pos, {x,1}); // pos に x を挿入
tr.erase(pos);        // pos を削除
tr.apply(l, r, val);  // [l,r) に val を加算
tr.reverse(l, r);     // [l,r) を反転

auto s = tr.prod(l, r).first; // [l,r) の和
```
