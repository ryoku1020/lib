---
title: SuperDisjointSetUnion
documentation_of: ../../ds/range_uf.hpp
---

# SuperDisjointSetUnion

長さ `L` の区間どうしをまとめて同一視するための Union-Find 拡張です。

## コンストラクタ

### `SuperDisjointSetUnion(int n)`

長さ `n` の列に対して初期化します。

## メソッド

### `int uf.root(int x)`

位置 `x` の代表元を返します。

### `void uf.merge(int l, int r, int L)`

区間 `[l,l+L)` と `[r,r+L)` を対応位置ごとに同一視します。

## 使用例

```cpp
SuperDisjointSetUnion uf(n);
uf.merge(l,r,len);
if(uf.root(x)==uf.root(y)){
    // same
}
```

## 注意

- [ds/super_dsu.hpp](/Users/ryoku_/Desktop/cp/lib/ds/super_dsu.hpp) と同内容の実装です。
