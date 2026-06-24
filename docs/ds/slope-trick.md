---
title: Slope Trick
documentation_of: ../../ds/slope-trick.hpp
---

# Slope Trick

下に凸な区分線形整数関数を、傾きが変化する点の多重集合として管理するデータ構造です。
DP の高速化に使います。

## 型

```cpp
SlopeTrick<T, MAXVALUE = numeric_limits<T>::max() / 2>
```

- `T` — 座標・値の型（`long long` など）
- `MAXVALUE` — 集合が空のときの番兵値

## コンストラクタ

### `SlopeTrick()`

$f(x) = 0$（定数関数）で初期化します。

## メンバ変数

- `T min_value` — 現在の関数の最小値

## メソッド

### `T st.get_ltop()`

左側 priority queue の最大値（傾き 0 以下の最右端）を返します。
左側が空なら `-MAXVALUE` を返します。

### `T st.get_rtop()`

右側 priority queue の最小値（傾き 0 以上の最左端）を返します。
右側が空なら `MAXVALUE` を返します。

- 注意: これらはオフセット補正前の生の値です。実際の傾き変化点とは異なります。通常は `min_value` と `slide_min` の組み合わせで結果を得てください。

### `void st.add_R(T a)`

$f(x) \leftarrow f(x) + \max(x - a, 0)$ を適用します（$x \geq a$ の傾きを $+1$）。

- 計算量: `O(log n)`

### `void st.add_L(T a)`

$f(x) \leftarrow f(x) + \max(a - x, 0)$ を適用します（$x \leq a$ の傾きを $-1$）。

- 計算量: `O(log n)`

### `void st.add_both(T a)`

$f(x) \leftarrow f(x) + |x - a|$ を適用します。
`add_L(a)` と `add_R(a)` の両方を呼ぶ等価な操作です。

- 計算量: `O(log n)`

### `void st.slide_min(T L, T R)`

$g(x) = \min_{x-R \leq a \leq x-L} f(a)$ に更新します。
最小値を達成する区間を左に `L`、右に `R` 広げる操作です。

- 制約: `L >= 0`, `R >= 0` を推奨（逆にすると最小値区間が縮む）
- 計算量: `O(1)`

## 境界・注意

- `min_value` は `add_*` のたびに自動で更新されます。
- `get_ltop()` / `get_rtop()` はオフセット補正なしの内部値を返します。精密な傾き変化点が必要な場合は `Loffset` / `Roffset` を自前で補正してください。
- 関数の値を逐一取得する API はありません。`min_value` のみが直接参照できます。

## 使用例: 最小コストでソート

各要素に $+1$ か $-1$ のコスト付き操作を繰り返して、非減少列にする最小操作回数:

```cpp
#include "ds/slope-trick.hpp"

SlopeTrick<long long> st;

for (int i = 0; i < n; i++) {
    st.add_L(a[i]);  // f(x) += max(a[i]-x, 0)
}

cout << st.min_value << "\n"; // 最小コスト
```

## 使用例: スライド最小値（区間 DP 高速化）

```cpp
SlopeTrick<long long> st;

// 何らかの DP を構築後...
st.slide_min(0, K); // 右方向に K だけ拡張
// min_value はそのままで、最小値区間が広がる
```

