---
title: treap
documentation_of: ../../ds/treap.hpp
---

# treap

implicit treap です。
列として扱い、挿入、削除、区間作用、区間反転、区間積を行えます。

## 型

### `treap<Info, Tag>`

`Info` は値モノイド、`Tag` は遅延作用です。
省略時は `Noninfo` / `Nontag`

## コンストラクタ

### `treap(int max_nodes)`

最大ノード数を指定して初期化します。

## 主なメソッド

### `void tr.build(const vc<value_type>& v)`
### `void tr.insert(int k, value_type v)`
### `void tr.erase(int k)`
### `void tr.apply(int l, int r, lazy_type x)`
### `void tr.reverse(int l, int r)`
### `value_type tr.prod(int l, int r)`

## 使用例

```cpp
treap<Info,Tag> tr(MAX_NODE);
tr.build(a);
tr.insert(pos,x);
tr.apply(l,r,tag);
auto s=tr.prod(l,r);
```

## 注意

- ノードプール上限を超えないように `max_nodes` を見積もる必要があります。
