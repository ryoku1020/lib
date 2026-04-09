---
title: AHU Algorithm (根付き木の同型判定)
documentation_of: ../../../not_lib/tree/ahu.hpp
---

# AHU Algorithm

Aho, Hopcroft, Ullman によって提案された、根付き木の同型判定（Tree Isomorphism）を行うためのアルゴリズムの実装です。
与えられた根付き木の構造を括弧の列 `(...)` で表現し、この文字列が一致するかどうかで木の同型判定が可能です。
※この実装はSuffix Array (`sf_array`) を用いて部分木のソートを高速に行う工夫がされています。

## ahu

```cpp
string ahu(const Tree& tree_, int root);
```

### 制約・引数
- `const Tree& tree_`: 対象の木。
- `int root`: 木の根とする頂点のインデックス。

### 戻り値
- `string`: 根付き木の構造を一意に表す括弧列（例: `((()())())`）。
同型な（同じ構造を持つ）根付き木は同じ文字列になります。この文字列同士を比較することで木の同型判定が行えます。

### 計算量
- $O(N \log N)$ (Suffix Array の構築に依存)
