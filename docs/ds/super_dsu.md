---
title: SuperDisjointSetUnion
documentation_of: ../../ds/super_dsu.hpp
---

# SuperDisjointSetUnion

`ds/range_uf.hpp` と同じ実装です。
詳しくは [range_uf.md](range_uf.md) を参照してください。

長さ `L` の区間どうしをまとめて同一視する Union-Find 拡張です。

## メソッド

### `int uf.root(int x)`

- 制約: `0<=x<n`

### `void uf.merge(int l, int r, int L)`

`[l, l+L)` と `[r, r+L)` を対応位置ごとに同一視します。

- 制約: `0<=l,r<=n`, `L>=0`, `l+L<=n`, `r+L<=n`
