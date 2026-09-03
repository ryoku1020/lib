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

## 計算量

- `n x m` 行列の加減算・スカラー倍・転置: 時間 `O(nm)`、返り値メモリ `O(nm)`
- `(n x k) * (k x m)` の行列積: 時間 `O(nkm)`、返り値メモリ `O(nm)`
- `n x n` 行列の `pow(e)`: 時間 `O(n^3 log e)`、メモリ `O(n^2)`
- `n x n` 行列の `det`, `inverse`: 時間 `O(n^3)`、メモリ `O(n^2)`
- `n x m` 行列の `rank`: `a=min(n,m)`, `b=max(n,m)` として時間 `O(a^2 b)`、メモリ `O(nm)`

## 境界・注意

- 各行の長さは同じでなければならず、行列の各次元は非負です（`assert` あり）。空の二次元配列から作った行列は `0 x 0` と解釈されます。
- 加減算では 2 行列の形、乗算では左の列数と右の行数が一致する必要があります（`assert` あり）。
- `pow`, `det`, `inverse` は正方行列を要求します（`assert` あり）。`pow` の指数は非負です。
- `det`, `rank`, `inverse` は非零要素での除算を使うため、`T` は体として扱える型を想定しています。通常の整数型では整数除算により正しい結果にならないため、`mint` や浮動小数点型を使ってください。
- 浮動小数点型では pivot の判定が厳密な `==0` であり、誤差対策付きの数値線形代数ではありません。
- 固定幅整数や modint の行列積は、結果の型へ格納するまでの中間和が実装内の `__int128` または `T` の範囲に収まる必要があります。

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
