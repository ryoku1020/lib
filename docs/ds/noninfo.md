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

- 汎用 treap
- 汎用 segment tree
- 値を持たないが構造だけ使いたいテンプレート
