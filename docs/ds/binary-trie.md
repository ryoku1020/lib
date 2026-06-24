---
title: Binary Trie
documentation_of: ../../ds/binary-trie.hpp
---

# Binary Trie

非負整数の多重集合を管理し、全体への XOR 操作や最小値・個数の取得を高速に行うトライ木です。

## 型

```cpp
BinaryTrie<T, depth>
```

- `T` — 要素の型（非負整数型: `int`, `long long` など）
- `depth` — ビット深さ（扱える値の範囲は `[0, 2^depth)` ）

## コンストラクタ

### `BinaryTrie<T, depth>()`

空のトライ木を作成します。

## メソッド

### `void tr.insert(T val, int x = 1)`

値 `val` を `x` 個追加します。
`x` に負の値を渡すと削除として機能します（個数が 0 未満にならないよう注意）。

- 制約: `val >= 0`, `0 <= val < 2^depth`
- 計算量: `O(depth)`

### `T tr.count(T val)`

値 `val` の個数（多重度）を返します。存在しない場合は `0`。

- 制約: `val >= 0`, `0 <= val < 2^depth`
- 計算量: `O(depth)`

### `void tr.all_xor(T x)`

木の全要素に `x` を XOR します。遅延的に offset に反映されるため `O(1)` です。

- 計算量: `O(1)`

### `T tr.find_min()`

木に含まれる要素（XOR offset 適用後）の最小値を返します。

- 制約: 木が空でないこと（`all_size > 0`）。空のとき `assert` で停止。
- 計算量: `O(depth)`

## 境界・注意

- `insert(val, x)` で `x` が負の場合、個数が負にならないよう呼び出し側で管理してください。
- `find_min` は `all_xor` による offset を考慮した実際の最小値を返します。

## 使用例

```cpp
#include "ds/binary-trie.hpp"

BinaryTrie<int, 20> tr; // [0, 2^20) の非負整数を管理

tr.insert(5);
tr.insert(3);
tr.insert(5);      // 5 は 2 個に

auto cnt = tr.count(5); // 2
auto mn  = tr.find_min(); // 3

tr.all_xor(7);     // 全要素に XOR 7
// 3^7=4, 5^7=2 → 最小は 2
auto mn2 = tr.find_min(); // 2

tr.insert(5, -1);  // 5 を 1 個削除
```

