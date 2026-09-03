---
title: Li Chao tree（CHT）
---

# Li Chao tree（CHT）

`ds/cht.hpp` は削除されました。代わりに用途に応じて以下の 3 つのファイルを使ってください。

| ファイル | いつ使う |
|---------|---------|
| [li-chao-tree.md](li-chao-tree.md) | x 座標が `[0, n)` の整数に収まる場合 |
| [dynamic-li-chao-tree.md](dynamic-li-chao-tree.md) | x 座標が大きい非負整数の場合、または疎なクエリ |
| [compressed-li-chao-tree.md](compressed-li-chao-tree.md) | クエリ x 座標が事前にすべてわかっている場合（定数倍最小） |

## 境界・注意

- このページは移行案内です。対応する `ds/cht.hpp` は存在しません。
- 直線追加と一点最小値クエリなら、基本は [li-chao-tree.md](li-chao-tree.md) を使います。
- 座標範囲が大きい場合は [dynamic-li-chao-tree.md](dynamic-li-chao-tree.md)、クエリ座標が先読みできる場合は [compressed-li-chao-tree.md](compressed-li-chao-tree.md) が向いています。
- 3 実装とも線分を追加する区間は半開区間です。動的版も座標範囲は `[0,n)` であり、負数・実数座標には対応していません。

## 計算量

`n` を座標範囲、`m` を圧縮後の座標数とします。

| 実装 | 構築 | 直線追加 | 線分追加 | 一点クエリ |
|------|------|----------|----------|--------------|
| `li_chao_tree` | `O(n)` | `O(log n)` | `O(log^2 n)` | `O(log n)` |
| `dynamic_li_chao_tree` | `O(log n)` | `O(log n)` | `O(log^2 n)` | `O(log n)` |
| `compressed_li_chao_tree` | `O(m log m)` | `O(log m)` | `O(log^2 m)` | `O(log m)` |

## 使用例

古い `cht.hpp` を使っていたコードは、座標条件に合わせて include 先を選びます。

```cpp
// x が 0 <= x < N に収まる場合
#include "ds/li_chao_tree/li-chao-tree.hpp"

// x が 10^18 など大きい場合
#include "ds/li_chao_tree/dynamic-li-chao-tree.hpp"

// クエリする x がすべて事前に分かる場合
#include "ds/li_chao_tree/compressed-li-chao-tree.hpp"
```
