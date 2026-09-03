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
- `*`, `*=`（点どうしは複素数積、スカラーとは定数倍）
- `/`, `/=`（スカラー除算）
- 単項 `-`（符号反転）
- `>>` — `x y` を入力
- `<=>` — 原点周りの偏角順比較
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

#### `ld abs() const`

原点からの Euclid 距離を返します。

#### `ld arg() const`

`atan2(y,x)` による偏角を返します。零ベクトルでは処理系の `atan2(0,0)` の値になります。

## `<=>`

点を原点周りの偏角順で比較します。概ね `atan2(y,x)` の昇順、すなわち負の偏角、正の x 軸、正の偏角、負の x 軸の順です。同じ半直線上では `x`, `y` で tie-break します。

比較の最初に `==` を使うため、`eps>0` では近い 2 点を同値とみなします。許容誤差付き等価関係は推移律を満たさない場合があるので、`sort`, `map`, `set` の比較として安全に使うには `eps==0` を推奨します。

## `convex_hull`

### `vc<Point>convex_hull(vc<Point>p, bool containboundary=false)`

点列 `p` の凸包を反時計回りの点列として返します。

- 重複点は自動除去されます（内部で unique 処理）
- `containboundary=false` なら共線（collinear）の点は凸包頂点に含まれません
- `containboundary=true` なら辺上の点も含めます
- 頂点数が 2 以下ならそのまま返します
- 先頭は `y` が最小、同値なら `x` が最小の頂点です

- 計算量: `O(n log n)`

### `vc<pair<Point,int>> ConvexHullIndex(vc<Point> p, bool containboundary=false)`

各点に元の添字を付けてから凸包を求め、`{点,元の添字}` の列を返します。重複座標がある場合は、ソート後に最初となる最小添字を残します。

- 計算量: `O(n log n)`

## 計算量まとめ

- `Point` の各演算、`Dot`, `Cross`, `abs`, `arg`: `O(1)`
- `convex_hull`, `ConvexHullIndex`: `O(n log n)` 時間、`O(n)` 補助領域

## 境界・注意

- 凸包の共線点はデフォルトでは除かれます。辺上の点も含めたい場合は `containboundary=true` を渡してください。
- 全点が共線で `containboundary=true` の場合、現行実装は内点を往路と復路の両方に含めることがあります。頂点の一意な集合が必要なら呼び出し側で重複を除いてください。
- `EPS` を変えたい場合は `#define EPS ...` を `#include "geometry/base.hpp"` より前に書いてください。`Point` のテンプレート引数 `eps` は `==` に使われる一方、`sign` や凸包の旋回判定はグローバルマクロ `EPS` を使います。
- 浮動小数の `EPS` を定義した状態で整数点を使う場合、`Point<long long>` のデフォルト `eps=EPS` は定数式変換に失敗します。`Point<long long,0>` のように明示してください。
- 整数座標では内積・外積・複素数積が `Point_type` の範囲に収まる必要があります。スカラー除算は整数型なら切り捨てです。また 0 除算は検査されません。
- `Dot` の符号による角度判定は、2 ベクトルがともに零ベクトルでない場合を想定しています。

## 使用例

```cpp
#define EPS 1e-9L
#include "geometry/base.hpp"

using P = Point<long long,0>;
using Q = Point<ld,EPS>;

// 外積で面積を求める（整数座標）
P a{0,0}, b{4,0}, c{0,3};
long long area2 = (b-a).Cross(c-a); // 三角形面積の 2 倍

// 凸包
vc<P>pts = {{0,0},{1,0},{0,1},{1,1},{0,0}}; // 重複あり
auto hull = convex_hull(pts);

// 原点周りの偏角順ソート
vc<P>dirs = {{1,0},{0,1},{-1,0},{0,-1}};
sort(all(dirs));
```
