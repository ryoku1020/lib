---
title: SuperDisjointSetUnion
documentation_of: ../../ds/super-dsu.hpp
---

# SuperDisjointSetUnion

`ds/range-uf.hpp` と同じ実装です。
詳しくは [range-uf.md](range-uf.md) を参照してください。

長さ `L` の区間どうしをまとめて同一視する Union-Find 拡張です。

## メソッド

### `int uf.root(int x)`

- 制約: `0<=x<n`

### `void uf.merge(int l, int r, int L)`

`[l, l+L)` と `[r, r+L)` を対応位置ごとに同一視します。

- 制約: `0<=l,r<=n`, `L>=0`, `l+L<=n`, `r+L<=n`

## 境界・注意

- このページは [range-uf.md](range-uf.md) と同じ実装への入口です。
- 区間は半開区間です。
- `merge(l,r,L)` は `i=0..L-1` について `l+i` と `r+i` を同一視します。

## 使用例

2 つの部分文字列が等しい、という条件をまとめて Union-Find に入れます。

```cpp
SuperDisjointSetUnion uf(n);

// [2,5) と [7,10) の対応位置を同一視
uf.merge(2,7,3);

if(uf.root(2)==uf.root(7)){
    // 位置 2 と 7 は同じグループ
}
```
