---
title: Disjoint Set Union
documentation_of: ../../ds/uf.hpp
---

# Disjoint Set Union

Union-Find です。
通常版 `DisjointSetUnion` と、成分ごとにデータを乗せられる `ExtraDisjointSetUnion` があります。

## `DisjointSetUnion`

### コンストラクタ

#### `DisjointSetUnion(int n)`

要素数 `n` で初期化します。初期状態では全要素が独立した成分です。

### メソッド

#### `int uf.root(int x)`
#### `int uf.leader(int x)`

`x` が属する成分の代表元を返します（`root` と `leader` は同じ）。

- 制約: `0 <= x < n`
- 計算量: ならし `O(alpha(n))`

#### `bool uf.same(int x, int y)`

`x` と `y` が同じ成分に属するか判定します。同じなら `true`。

- 制約: `0 <= x, y < n`
- 計算量: ならし `O(alpha(n))`

#### `bool uf.merge(int x, int y)`

`x` と `y` の成分を併合します。
新しく併合した場合は `true`、すでに同じ成分だった場合は `false` を返します。

- 制約: `0 <= x, y < n`
- 計算量: ならし `O(alpha(n))`

#### `int uf.size(int x)`

`x` が属する成分の要素数を返します。

- 制約: `0 <= x < n`
- 計算量: ならし `O(alpha(n))`

## `ExtraDisjointSetUnion<T, op>`

各連結成分に値を乗せる Union-Find です。
成分を併合するとき、代表元の値が `op(data[a], data[b])` に更新されます。

### コンストラクタ

#### `ExtraDisjointSetUnion<T, op>(int n, T e)`

各成分データを初期値 `e` で初期化します。

### メソッド

#### `T& uf[i]`

`i` が属する成分の代表元データへの参照を返します。
読み書き両方できます。

- 計算量: ならし `O(alpha(n))`

`merge`/`same`/`root`/`size` は `DisjointSetUnion` と同じです。

### 使用例

```cpp
auto add_op = [](long long a, long long b) { return a + b; };
ExtraDisjointSetUnion<long long, add_op> uf(n, 0);

uf[0] = 10;
uf[1] = 20;
uf.merge(0, 1);
cout << uf[0]; // 30 (op(10, 20))
```

## 計算量

- 全メソッド: ならし `O(alpha(n))`（alpha はアッカーマン逆関数、実質定数）

## 境界・注意

- 頂点番号は 0-indexed です。
- `ExtraDisjointSetUnion` の `operator[]` は常にその時点の代表元のデータを返します。
  `merge` 後は代表元が変わる可能性があるので、インデックスではなく `uf[i]` で常に参照してください。

## 使用例

```cpp
#include "ds/uf.hpp"

DisjointSetUnion uf(n);
uf.merge(0, 1); // true
uf.merge(1, 2); // true
uf.merge(0, 2); // false (すでに同じ成分)

if (uf.same(0, 2)) {
    // true
}
cout << uf.size(0); // 3
```
