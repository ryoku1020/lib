---
title: Disjoint Set Union
documentation_of: ../../ds/uf.hpp
---

# Disjoint Set Union

Union-Find です。
通常版 `DisjointSetUnion` と、成分ごとにデータを持てる `ExtraDisjointSetUnion` があります。

## `DisjointSetUnion`

### コンストラクタ

#### `DisjointSetUnion(int n)`

要素数 `n` で初期化します。

## メソッド

### `int uf.root(int x)`
### `int uf.leader(int x)`

`x` が属する成分の代表元を返します。

### `bool uf.same(int x, int y)`

`x` と `y` が同じ成分に属するか判定します。

### `bool uf.merge(int x, int y)`

`x` と `y` の成分を併合します。
すでに同じ成分なら `false`、新しく併合したら `true` を返します。

### `int uf.size(int x)`

`x` が属する成分サイズを返します。

## 使用例

```cpp
#include "ds/uf.hpp"

DisjointSetUnion uf(n);
uf.merge(a,b);
if(uf.same(u,v)){
    // same component
}
```

## `ExtraDisjointSetUnion<T, op>`

各連結成分にデータを載せる Union-Find です。
成分併合時に `data[x]=op(data[y],data[x])` の形でマージされます。

### コンストラクタ

#### `ExtraDisjointSetUnion<T,op>(int n, T e)`

各成分データを初期値 `e` で初期化します。

### 追加機能

#### `T& uf[i]`

`i` が属する成分データへの参照を返します。

## 使用例

```cpp
long long add_op(long long a,long long b){
    return a+b;
}

ExtraDisjointSetUnion<long long,add_op> uf(n,0);
uf[0]=10;
uf[1]=20;
uf.merge(0,1);
auto sum=uf[0];
```

## 計算量

- `root`, `leader`, `same`, `merge`, `size`, `operator[]`
  ならし `O(alpha(n))`

## 注意

- 頂点番号は 0-indexed です。
- `ExtraDisjointSetUnion` で `operator[]` を使うときは、その時点の代表元にアクセスされます。
