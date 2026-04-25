---
title: Point / ConvexHull
documentation_of: ../../geometry/hoge.hpp
---

# Point / ConvexHull

2 次元点と凸包です。

## `Point<Point_type, eps>`

### メンバ

- `x`, `y`

### 演算

- `+`, `-`, `+=`, `-=`
- `==`, `!=`

### メソッド

- `Dot`
  内積
- `Cross`
  外積

## `ConvexHull`

### `pair<vc<point>,vc<point>> ConvexHull(vc<point> points)`

下側凸包と上側凸包を返します。

## 使用例

```cpp
#include "geometry/hoge.hpp"

using P=Point<long long>;
vector<P> ps={{0,0},{1,0},{0,1},{1,1}};
auto [lower,upper]=ConvexHull(ps);
```
