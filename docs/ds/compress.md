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
最初の `find` / `find_next` / `size` で `build` が自動実行されます。

- 計算量: `O(xs.size())`

## メソッド

### `void cp.push(T v)`

値 `v` を追加します。構築済みの場合も `built` が解除され、次の `build` / `find` / `find_next` / `size` で再構築されます。

- 計算量: ならし `O(1)`

### `void cp.build()`

追加した値を sort・unique してインデックスを確定します。
`find` / `find_next` / `size` を呼ぶと自動で呼ばれます。

- 計算量: `O(k log k)`（未構築の場合）

### `int cp.find(T v)`

`v` の圧縮後インデックスを返します。
存在しなければ `-1`。

- 計算量: `O(log k)` (k は登録済み要素数)

### `int cp.find_next(T v)`

`v` 以上の最小値の圧縮後インデックスを返します（`lower_bound`）。
該当する値がなければ `size()` を返します。

- 計算量: `O(log k)`

### `int cp.size()`

圧縮後の値の種類数を返します。

- 計算量: 構築済みなら `O(1)`

### `T cp[int i]`

圧縮後インデックス `i` の元の値を返します。

- 制約: `build()` 済み、`0<=i<size()`
- 計算量: `O(1)`

## 境界・注意

- `find` は完全一致でなければ `-1` を返します。"この値以上" を調べたいときは `find_next` を使ってください。
- 0-indexed です。
- `operator[]` は `const` であり、内部では `build` を呼びません。アクセス前に `build()`、`find`、`find_next`、`size` のいずれかで構築を完了してください。

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
