---
title: AHU Algorithm
documentation_of: ../../../.not_lib/tree/ahu.hpp
---

# AHU Algorithm

根付き木の同型判定用エンコードを返す関数です。
同型な根付き木は同じ括弧列表現になります。

## 関数

### `string ahu(const Tree& tree_, int root)`

木 `tree_` を `root` で根付き木とみなし、その構造を表す文字列を返します。

## 使用例

```cpp
#include ".not_lib/tree/ahu.hpp"

string s1=ahu(tree1,r1);
string s2=ahu(tree2,r2);
bool iso=(s1==s2);
```

## 注意

- 内部で suffix array を使って子部分木の順序を決定しています。
- 根付き木として比較したいときに使います。
