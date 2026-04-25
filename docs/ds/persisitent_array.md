---
title: PersistentArray
documentation_of: ../../ds/persisitent_array.hpp
---

# PersistentArray

B 分木型の永続配列です。
更新後も元バージョンを保持します。

## 型

### `PersistentArray<T, B>`

- `T`
  値型
- `B`
  分岐数

## 主なメソッド

### `Node* build(int n, T x)`

長さ `n`、初期値 `x` の配列を作り、根を返します。

### `Node* change(int pos, T x, Node* root)`

`root` を元に `pos` を `x` に変更した新バージョンの根を返します。

### `T get(int pos, Node* root)`

指定バージョンでの `pos` の値を返します。

## 使用例

```cpp
PersistentArray<int,2> pa;
auto r0=pa.build(n,0);
auto r1=pa.change(3,10,r0);
int x=pa.get(3,r1);
int y=pa.get(3,r0);
```
