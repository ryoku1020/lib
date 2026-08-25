---
title: noninfo / nontag
documentation_of: ../../ds/utility/noninfo.hpp
---

# noninfo / nontag

値を持たないデータ構造テンプレート用のダミー `info` / `tag` です。

## `noninfo`

`value_type = monostate` で、`op`, `e`, `leaf` を何もしない形で定義しています。

## `nontag<info>`

遅延作用が不要なときのダミー `tag` です。

## 用途

- 汎用 treap
- 汎用 segment tree
- 値を持たないが構造だけ使いたいテンプレート

## 境界・注意

- `noninfo` の値は `monostate` なので、値そのものを読み出して意味のある計算をする用途には向きません。
- `nontag<info>` は遅延作用を使わないことを明示するための型です。

## 使用例

遅延を使わない treap を、`tag` だけダミーにして宣言します。

```cpp
#include "ds/utility/noninfo.hpp"
#include "ds/ordered/treap.hpp"

treap<info,nontag<info>> tr(max_nodes);
```
