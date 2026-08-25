---
title: matrix
documentation_of: ../../math/mat.hpp
---

# matrix

行列ライブラリです。
加減乗算、転置、累乗、行列式、階数、逆行列を持ちます。

## 型

```cpp
matrix<T>
```

- `T` — 要素の型（`long long`, `mint` など四則演算と `0/1` 判定ができる型）

## コンストラクタ

### `matrix(vvc<T> a)`

二次元配列から行列を作ります。

### `matrix(int n, int m)`

`n × m` のゼロ行列を作ります。

## メソッド

### `static matrix matrix::unit(int n)`

`n × n` 単位行列を返します。

### `matrix trans() const`

転置行列を返します。`n × m` → `m × n`。

### `matrix pow(long long k)`

行列累乗 $A^k$ を返します。

- 制約: 正方行列であること、`k >= 0`
- 計算量: `O(n^3 log k)`

### `T det() const`

行列式を返します。

- 制約: 正方行列であること
- 計算量: `O(n^3)`

### `int rank() const`

階数を返します。

- 計算量: `O(n^2 m)`（`n × m` 行列）

### `optional<matrix> inverse() const`

逆行列が存在すれば `optional<matrix>` に包んで返します。
存在しないとき（行列式が 0 のとき）は `nullopt` を返します。

- 制約: 正方行列であること
- 計算量: `O(n^3)`

## 演算

- `+`, `-`, `*`（行列どうし、またはスカラーとの積）
- `+=`, `-=`, `*=`

## 境界・注意

- `pow`, `det`, `inverse` は正方行列が必要です。非正方行列を渡すと未定義動作（または `assert`）です。
- `T` が整数型のとき `det` の結果は厳密に正しくない場合があります（ガウスの消去で除算が発生するため）。`mint` や `double` で使うのが安全です。

## 使用例: 行列累乗でフィボナッチ数列

```cpp
#include "math/mat.hpp"

using mint = static_modint<1000000007>;
using Mat = matrix<mint>;

Mat A({{1,1},{1,0}});
Mat res = A.pow(n); // F(n), F(n-1) が res[0][0], res[0][1]
```

## 使用例: 逆行列

```cpp
auto inv = A.inverse();
if (inv) {
    // *inv が逆行列
} else {
    // 逆行列なし（行列式 == 0）
}
```
