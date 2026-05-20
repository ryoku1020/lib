---
title: PersistentArray
documentation_of: ../../ds/persistent-array.hpp
---

# PersistentArray

B 分木型の永続配列です。
`change` のたびに新しいバージョン（root ポインタ）を返し、古いバージョンも保持されます。

## 型

```cpp
PersistentArray<T, B>
```

- `T` — 要素の型
- `B` — 分岐数（通常 `2` または `4`）。大きくするほど木の高さが低くなり定数倍で有利ですが、1ノードあたりのコストが増えます。

## メソッド

### `Node* pa.build(int n, T x)`

長さ `n`、全要素が `x` の初期配列を作り、root ポインタを返します。

- 計算量: `O(n / B + log_B n)`

### `Node* pa.change(int pos, T x, Node* root)`

`root` バージョンの `pos` 番目を `x` に変更した新しいバージョンの root を返します。
元の `root` はそのまま保持されます。

- 制約: `0 <= pos < n`
- 計算量: `O(log_B n)`

### `T pa.get(int pos, Node* root)`

`root` バージョンの `pos` 番目の値を返します。

- 制約: `0 <= pos < n`
- 計算量: `O(log_B n)`

## 使用例

```cpp
#include "ds/persistent-array.hpp"

PersistentArray<int, 2> pa;

auto r0 = pa.build(n, 0);     // バージョン 0: 全要素 0

auto r1 = pa.change(3, 10, r0); // r0 の pos=3 を 10 にした r1
auto r2 = pa.change(5, 7, r1);  // r1 の pos=5 を 7 にした r2

int a = pa.get(3, r2); // 10
int b = pa.get(3, r0); // 0  (r0 は変わっていない)
int c = pa.get(5, r2); // 7
```

## 注意

- 各 `build` / `change` の呼び出しでノードを動的確保します。大量のバージョンを作るとメモリ使用量が `O(Q log_B n)` になります。
- `B = 2` のとき高さは `O(log_2 n)` = `O(log n)` です。
