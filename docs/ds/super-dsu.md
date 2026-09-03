---
title: super_disjoint_set_union
documentation_of: ../../ds/union_find/super-dsu.hpp
---

# super_disjoint_set_union

`ds/union_find/range-uf.hpp` と同じ実装です。
詳しくは [range-uf.md](range-uf.md) を参照してください。

長さ `L` の区間どうしをまとめて同一視する Union-Find 拡張です。

## コンストラクタ

### `super_disjoint_set_union(int n)`

長さ `n` の列に対して初期化します。

- 制約: `n>=0`
- 計算量: `O(n log n)`

## メソッド

### `int uf.root(int x)`

位置 `x` の代表元を返します。

- 制約: `0<=x<n`
- 計算量: ならし `O(alpha(n))`

### `void uf.merge(int l, int r, int L)`

`[l, l+L)` と `[r, r+L)` を対応位置ごとに同一視します。

- 制約: `0<=l,r<=n`, `L>=0`, `l+L<=n`, `r+L<=n`
- `l==r` または `L==0` のときは何もしません。
- 計算量: 1 回の最悪は `O(L alpha(n))`

## 計算量

構築時間・メモリは `O(n log n)`、`root` はならし `O(alpha(n))`、`merge(l,r,L)` は 1 回の最悪 `O(L alpha(n))` です。内部で同じ区間ペアがすでに併合済みなら、その下の再帰は打ち切られます。

## 境界・注意

- このページは [range-uf.md](range-uf.md) と同じ実装への入口です。
- 区間は半開区間です。
- `merge(l,r,L)` は `i=0..L-1` について `l+i` と `r+i` を同一視します。

## 使用例

2 つの部分文字列が等しい、という条件をまとめて Union-Find に入れます。

```cpp
super_disjoint_set_union uf(n);

// [2,5) と [7,10) の対応位置を同一視
uf.merge(2,7,3);

if(uf.root(2)==uf.root(7)){
    // 位置 2 と 7 は同じグループ
}
```
