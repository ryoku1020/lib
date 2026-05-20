---
title: PersistentUnionFind
documentation_of: ../../ds/persistent-uf.hpp
---

# PersistentUnionFind

永続 Union-Find です。
各 `merge` が新しいバージョン（node ポインタ）を返し、過去のバージョンも保持されます。
内部で `PersistentArray<int, B>` を使っています。

## 型

```cpp
PersistentUnionFind<B = 2>
```

- `B` — 内部 B 分木の分岐数（通常 `2`）

## メソッド

### `node uf.build(int n)`

要素数 `n` の初期バージョン（全要素が独立した成分）を返します。

- 計算量: `O(n)`

### `int uf.root(int x, node root)`

`root` バージョンで `x` の代表元を返します。

- 制約: `0 <= x < n`
- 計算量: `O(log^2 n)`（パス圧縮なし）

### `bool uf.same(int a, int b, node root)`

`root` バージョンで `a` と `b` が同じ成分なら `true`、異なれば `false` を返します。

- 制約: `0 <= a, b < n`
- 計算量: `O(log^2 n)`

### `node uf.merge(int a, int b, node root)`

`root` バージョンで `a` と `b` の成分を併合した新しいバージョンを返します。
すでに同じ成分の場合は `root` をそのまま返します。

- 制約: `0 <= a, b < n`
- 計算量: `O(log^2 n)`

## 使用例

```cpp
#include "ds/persistent-uf.hpp"

PersistentUnionFind<2> uf;

auto r0 = uf.build(n);           // バージョン 0
auto r1 = uf.merge(0, 1, r0);   // 0 と 1 をマージした r1
auto r2 = uf.merge(2, 3, r1);   // さらに 2 と 3 をマージした r2

bool b1 = uf.same(0, 1, r2); // true
bool b2 = uf.same(0, 2, r2); // false
bool b0 = uf.same(0, 1, r0); // false (r0 は元のまま)
```

## 注意

- パス圧縮を行わないため `root` / `same` は `O(log^2 n)` です（union by size を使うため）。
- `merge` のたびに `O(log n)` ノードが生成されます。`Q` 回の操作で `O(Q log n)` ノードを消費します。
