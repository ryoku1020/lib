---
title: compresser
documentation_of: ../../ds/compress.hpp
---

# compresser

座標圧縮ユーティリティです。
値の集合を `0, 1, ..., k-1` の整数に圧縮します。

## コンストラクタ

### `compresser<T>(int n)`

`n` 要素を事前確保して初期化します。

### `compresser<T>(const vc<T>& xs)`

配列 `xs` を初期値として初期化します。
内部で `build` は自動で行われます。

## メソッド

### `void cp.push(T v)`

値 `v` を追加します。`build` 前に呼ぶ必要があります。

### `void cp.build()`

追加した値を sort・unique してインデックスを確定します。
`find` / `find_next` / `size` / `operator[]` を呼ぶと自動で呼ばれます。

### `int cp.find(T v)`

`v` の圧縮後インデックスを返します。
存在しなければ `-1`。

- 計算量: `O(log k)` (k は登録済み要素数)

### `int cp.find_next(T v)`

`v` 以上の最小値の圧縮後インデックスを返します（`lower_bound`）。

- 計算量: `O(log k)`

### `int cp.size()`

圧縮後の値の種類数を返します。

### `T cp[int i]`

圧縮後インデックス `i` の元の値を返します。

## 境界・注意

- `find` は完全一致でなければ `-1` を返します。"この値以上" を調べたいときは `find_next` を使ってください。
- 0-indexed です。
- `operator[]` はアクセス前に `build` が済んでいる必要があります（内部で `build` を呼ぶため、最初にアクセスすれば OK）。

## 使用例

```cpp
#include "ds/compress.hpp"

compresser<long long> cp(n);
for(int i=0;i<n;i++) cp.push(a[i]);

// 圧縮後インデックス取得
int id = cp.find(a[i]); // 存在しなければ -1
int sz = cp.size();     // 種類数

// 元の値への復元
long long orig = cp[id];

// lower_bound 相当
int lb = cp.find_next(x); // x 以上の最小要素のインデックス
```
