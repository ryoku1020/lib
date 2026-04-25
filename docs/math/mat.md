---
title: Matrix
documentation_of: ../../math/mat.hpp
---

# Matrix

行列ライブラリです。
加減乗算、転置、累乗、行列式、階数、逆行列を持ちます。

## 型

### `Matrix<T>`

`n x m` 行列です。

## コンストラクタ

### `Matrix(vvc<T> a)`
### `Matrix(int n, int m)`

## メソッド

### `Matrix trans() const`

転置を返します。

### `static Matrix unit(int n)`

`n x n` 単位行列を返します。

### `Matrix pow(long long k)`

行列累乗を返します。
正方行列を仮定します。

### `T det() const`

行列式を返します。

### `int rank() const`

階数を返します。

### `optional<Matrix> inverse() const`

逆行列が存在すれば返します。
存在しなければ `nullopt` です。

## 演算

- `+`, `-`, `*`
- `+=`, `-=`, `*=`

## 使用例

```cpp
#include "math/mat.hpp"

Matrix<long long> A({{1,1},{1,0}});
auto B=A.pow(10);
auto d=A.det();
```

## 注意

- `pow`, `det`, `inverse` は正方行列前提です。
- `T` は四則演算と `0/1` 判定ができる型を想定しています。
