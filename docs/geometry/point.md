---
title: Point / ConvexHull
documentation_of: ../../geometry/point.hpp
---

# Point / ConvexHull

2 次元点と凸包です。

## `Point<Point_type, eps>`

```cpp
Point<Point_type, eps = 0>
```

- `Point_type` — 座標の型（`long long`, `double` など）
- `eps` — `==` 判定の許容誤差（デフォルト 0: 完全一致）

### メンバ

- `Point_type x, y`

### 演算子

- `+`, `-`, `+=`, `-=`（点どうしの加減算）
- 単項 `-`（符号反転）
- `==` — `|p.x - x| <= eps && |p.y - y| <= eps`
- `!=` — `p.x == x && p.y == y`（完全一致判定、`eps` 非考慮。注意: `!=` は `==` の否定ではありません）

### メソッド

#### `Point_type Dot(const Point& b)`

内積 `x*b.x + y*b.y` を返します。

- `> 0` — 鋭角（90度未満）
- `= 0` — 直角（垂直）
- `< 0` — 鈍角（90度超）

#### `Point_type Cross(const Point& b)`

外積 `x*b.y - y*b.x` を返します。

- `> 0` — `b` は `a`（`this`）から見て反時計回り方向
- `= 0` — 平行（同一直線上）
- `< 0` — `b` は `a` から見て時計回り方向

## `ConvexHull`

### `pair<vc<point>, vc<point>> ConvexHull(vc<point> points)`

点群 `points` の凸包を**下側凸包**と**上側凸包**に分けて返します。

- 返り値: `{lower, upper}`
  - `lower` — 左から右へ並ぶ下側の頂点列
  - `upper` — 右から左へ並ぶ上側の頂点列
- 重複点は自動除去されます（内部で unique 処理）
- 共線（collinear）の点は凸包頂点に含まれません（strictly convex）
- `points.size() <= 2` のとき `{points, points}` を返します

- 計算量: `O(n log n)`

## 使用例

```cpp
#include "geometry/point.hpp"

using P = Point<long long>;

// 外積で面積を求める（整数座標）
P a{0,0}, b{4,0}, c{0,3};
long long area2 = (b-a).Cross(c-a); // 三角形面積の 2 倍

// 凸包
vc<P> pts = {{0,0},{1,0},{0,1},{1,1},{0,0}}; // 重複あり
auto [lower, upper] = ConvexHull(pts);
// lower = {(0,0),(1,0),(1,1)}  左→右→右上
// upper = {(1,1),(0,1),(0,0)}  右上→左上→左

// 全凸包頂点（閉じた多角形として）
vc<P> hull;
for (auto& p : lower) hull.push_back(p);
for (int i = 1; i + 1 < (int)upper.size(); i++) hull.push_back(upper[i]);
```

## 注意

- `!=` の実装が `p.x == x && p.y == y` であり、`==` の否定になっていません。`eps > 0` のとき `==` と `!=` は非対称です。
- 凸包の共線点は除かれます。辺上の点も含めたい場合は実装を修正する必要があります。
- 浮動小数点で使う場合は `eps` を適切に設定してください（例: `Point<double, 1e-9>`）。
