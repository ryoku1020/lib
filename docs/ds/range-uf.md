---
title: super_disjoint_set_union
documentation_of: ../../ds/union_find/range-uf.hpp
---

# super_disjoint_set_union

長さ `L` の区間どうしをまとめて同一視する Union-Find 拡張です。
`merge(l, r, L)` で `[l, l+L)` と `[r, r+L)` の対応位置をすべて同一視します。

## コンストラクタ

### `super_disjoint_set_union(int n)`

長さ `n` の列に対して初期化します。

## メソッド

### `int uf.root(int x)`

位置 `x` の代表元を返します。

- 制約: `0<=x<n`
- 計算量: ならし `O(alpha(n))`

### `void uf.merge(int l, int r, int L)`

区間 `[l, l+L)` と `[r, r+L)` を対応位置ごとに同一視します。
すなわち `l+i` と `r+i` を（`0<=i<L` のすべてについて）同じ成分にします。

- 制約: `0<=l,r<=n`, `L>=0`, `l+L<=n`, `r+L<=n`
- `l==r` または `L==0` のときは何もしません
- 計算量: `O(L * alpha(n))` ならし（最悪 `O(L log L)` 程度）

## 境界・注意

- `ds/union_find/super-dsu.hpp` と同じ実装です。
- 内部で複数サイズの Union-Find を持ちます。
- `root(x)` は 0-indexed です。

## 使用例

```cpp
#include "ds/union_find/range-uf.hpp"

super_disjoint_set_union uf(n);

// [3, 6) と [7, 10) の対応要素を同一視
// 3↔7, 4↔8, 5↔9
uf.merge(3, 7, 3);

if (uf.root(3) == uf.root(7)) {
    // true: 対応位置が同一視されている
}
```
