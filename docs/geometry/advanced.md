---
title: 幾何追加 API | 最大長方形
documentation_of: ../../geometry/max-rectangle.hpp
keywords: max_rectangle, maximal rectangle, binary matrix
---

# 幾何追加 API

## 0/1 行列の最大長方形 (`max_rectangle`)

行列中の 1 のみからなる極大な矩形を探します。

```cpp
#include "geometry/max-rectangle.hpp"

auto [rect, area] = max_rectangle(a);
// rect = {left, right, top, bottom} (全端点を含む)
```

- `max_rectangle(v)` は `{座標, 面積}` を返します。座標は `{xl,xr,yl,yr}` で、左右・上下端を含む閉区間です。
- `v` は高さ・幅がともに 1 以上で、全行が同じ幅の 0/1 行列である必要があります。
- 1 のない行列では `{0,-1,0,-1}` と面積 0 を返します。
- 時間 `O(HW)`、追加領域 `O(W)`。
- `max_rectangle(v, eval)` は候補矩形ごとに `eval(xl,xr,yl,yr)` を呼び、`int` の最大値と座標を返します。面積以外を最大化する用途です。`eval` の最大値の型は `int` 固定で、`ll` へは一般化されません。

`max_rectangle` は配列に対する DP 関数で、点・線分・多角形の幾何 API ではありません。
