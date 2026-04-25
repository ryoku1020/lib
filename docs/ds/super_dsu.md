---
title: SuperDisjointSetUnion
documentation_of: ../../ds/super_dsu.hpp
---

# SuperDisjointSetUnion

区間どうしの同一視を高速に処理する Union-Find 拡張です。
[docs/ds/range_uf.md](/Users/ryoku_/Desktop/cp/lib/docs/ds/range_uf.md) と同内容です。

## 主なメソッド

### `int uf.root(int x)`
### `void uf.merge(int l, int r, int L)`

`[l,l+L)` と `[r,r+L)` を対応位置ごとに併合します。
