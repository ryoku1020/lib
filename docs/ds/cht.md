---
title: Li Chao Tree（CHT）
---

# Li Chao Tree（CHT）

`ds/cht.hpp` は削除されました。代わりに用途に応じて以下の 3 つのファイルを使ってください。

| ファイル | いつ使う |
|---------|---------|
| [li-chao-tree.md](li-chao-tree.md) | x 座標が `[0, n)` の整数に収まる場合 |
| [dynamic-li-chao-tree.md](dynamic-li-chao-tree.md) | x 座標が大きい・負の値・実数の場合、または疎なクエリ |
| [compressed-li-chao-tree.md](compressed-li-chao-tree.md) | クエリ x 座標が事前にすべてわかっている場合（定数倍最小） |

## 境界・注意

- このページは移行案内です。対応する `ds/cht.hpp` は存在しません。
- 直線追加と一点最小値クエリなら、基本は [li-chao-tree.md](li-chao-tree.md) を使います。
- 座標範囲が大きい場合は [dynamic-li-chao-tree.md](dynamic-li-chao-tree.md)、クエリ座標が先読みできる場合は [compressed-li-chao-tree.md](compressed-li-chao-tree.md) が向いています。

## 使用例

古い `cht.hpp` を使っていたコードは、座標条件に合わせて include 先を選びます。

```cpp
// x が 0 <= x < N に収まる場合
#include "ds/li-chao-tree.hpp"

// x が 10^18 など大きい場合
#include "ds/dynamic-li-chao-tree.hpp"

// クエリする x がすべて事前に分かる場合
#include "ds/compressed-li-chao-tree.hpp"
```
