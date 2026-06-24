---
title: Noninfo / Nontag
documentation_of: ../../ds/noninfo.hpp
---

# Noninfo / Nontag

値を持たないデータ構造テンプレート用のダミー `Info` / `Tag` です。

## `Noninfo`

`value_type = monostate` で、`op`, `e`, `leaf` を何もしない形で定義しています。

## `Nontag<Info>`

遅延作用が不要なときのダミー `Tag` です。

## 用途

- 汎用 Treap
- 汎用 segment tree
- 値を持たないが構造だけ使いたいテンプレート

## 境界・注意

- `Noninfo` の値は `monostate` なので、値そのものを読み出して意味のある計算をする用途には向きません。
- `Nontag<Info>` は遅延作用を使わないことを明示するための型です。

## 使用例

遅延を使わない Treap を、`Tag` だけダミーにして宣言します。

```cpp
#include "ds/noninfo.hpp"
#include "ds/treap.hpp"

Treap<Info,Nontag<Info>> tr(max_nodes);
```
