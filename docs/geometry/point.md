---
title: Point / convex_hull
documentation_of: ../../geometry/base.hpp
---

# Point / convex_hull

2 次元点、幾何 primitive、凸包です。

## `Point<Point_type, eps>`

```cpp
Point<Point_type, eps = EPS>
```

- `Point_type` — 座標の型（`long long`, `double` など）
- `eps` — `==` 判定の許容誤差（デフォルトは `EPS`。未定義なら 0）

### メンバ

- `Point_type x, y`

### 演算子

- `+`, `-`, `+=`, `-=`（点どうしの加減算）
- 単項 `-`（符号反転）
- `>>` — `x y` を入力
- `<=>` — `x`, `y` の辞書順比較
- `==` — `|p.x - x| <= eps && |p.y - y| <= eps`
- `!=` — `==` の否定

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

## `<=>`

点 `a`, `b` を `x`, `y` の辞書順で比較します。

- `x` が小さい点を先に並べます
- `x` が同じなら `y` が小さい点を先に並べます
- `==` の `eps` 判定は使わないので、`map` や `set` のキーとして使えます

## `convex_hull`

### `vc<Point>convex_hull(vc<Point>p, bool containboundary=false)`

点列 `p` の凸包を反時計回りの点列として返します。

- 重複点は自動除去されます（内部で unique 処理）
- `containboundary=false` なら共線（collinear）の点は凸包頂点に含まれません
- `containboundary=true` なら辺上の点も含めます
- 頂点数が 2 以下ならそのまま返します

- 計算量: `O(n log n)`

## 境界・注意

- 凸包の共線点はデフォルトでは除かれます。辺上の点も含めたい場合は `containboundary=true` を渡してください。
- `EPS` を変えたい場合は `#define EPS ...` を `#include "geometry/base.hpp"` より前に書いてください。

## 使用例

```cpp
#define EPS 1e-9L
#include "geometry/base.hpp"

using P = Point<long long>;
using Q = Point<ld>;

// 外積で面積を求める（整数座標）
P a{0,0}, b{4,0}, c{0,3};
long long area2 = (b-a).Cross(c-a); // 三角形面積の 2 倍

// 凸包
vc<P>pts = {{0,0},{1,0},{0,1},{1,1},{0,0}}; // 重複あり
auto hull = convex_hull(pts);

// 座標の辞書順ソート
vc<P>dirs = {{1,0},{0,1},{-1,0},{0,-1}};
sort(all(dirs));
```
