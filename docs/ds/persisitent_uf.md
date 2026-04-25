---
title: PersistentUnionFind
documentation_of: ../../ds/persisitent_uf.hpp
---

# PersistentUnionFind

永続 Union-Find です。
各マージ後のバージョンを根ポインタで保持できます。

## 型

### `PersistentUnionFind<B>`

内部で `PersistentArray<int,B>` を使います。

## メソッド

### `node uf.build(int n)`

初期バージョンを返します。

### `int uf.root(int x, node root)`
### `int uf.same(int a, int b, node root)`

指定バージョンでの root / same 判定です。

### `node uf.merge(int a, int b, node root)`

指定バージョンにマージした新しいバージョンを返します。

## 使用例

```cpp
PersistentUnionFind<2> uf;
auto r0=uf.build(n);
auto r1=uf.merge(0,1,r0);
bool b=uf.same(0,1,r1);
```
