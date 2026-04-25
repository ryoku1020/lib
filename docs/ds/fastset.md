---
title: FastSet
documentation_of: ../../ds/fastset.hpp
---

# FastSet

`[0,n)` 上の整数集合を管理する高速 bitset 木です。
挿入、削除、存在判定、次要素・前要素探索ができます。

## コンストラクタ

### `FastSet(int n)`

宇宙集合を `[0,n)` として初期化します。

## メソッド

### `int fs.insert(int x)`

`x` を挿入します。
新しく入ったなら `1`、すでに存在したなら `0` を返します。

### `int fs.erase(int x)`

`x` を削除します。
存在していたなら `1`、なければ `0` を返します。

### `int fs.count(int x)`

`x` が存在すれば `1`、なければ `0` を返します。

### `int fs.next(int x)`

`x` 以上の最小の要素を返します。
存在しなければ `n` を返します。

### `int fs.prev(int x)`

`x` 以下の最大の要素を返します。
存在しなければ `-1` を返します。

## メンバ

- `size`
  現在の集合サイズです。

## 使用例

```cpp
#include "ds/fastset.hpp"

FastSet fs(n);
fs.insert(3);
fs.insert(10);

int a=fs.next(4);  // 10
int b=fs.prev(9);  // 3
```

## 注意

- 値域は `[0,n)` です。
- 返り値 `n` と `-1` は番兵として使います。
