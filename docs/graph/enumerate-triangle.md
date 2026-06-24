---
title: enumerate-triangle
documentation_of: ../../graph/enumerate-triangle.hpp
---

# enumerate-triangle

無向グラフ中の三角形を列挙します。

## 関数

### `void enumerate_triangle(const G<0,T>& g, F f)`

各三角形 `(a,b,c)` に対して `f(a,b,c)` を呼びます。

- 計算量: 典型的には `O(m sqrt(m))` 系

## 境界・注意

- 無向グラフを前提としています。
- 同じ三角形は 1 回ずつ列挙されます。

## 使用例

```cpp
#include "graph/enumerate-triangle.hpp"

long long cnt=0;
enumerate_triangle(g,[&](int a,int b,int c){
    cnt++;
});
```

