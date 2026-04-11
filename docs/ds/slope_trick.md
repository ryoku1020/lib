---
title: Slope Trick
documentation_of: ../../ds/slope_trick.hpp
---

# Slope Trick

下に凸な関数の最小値や形状を、関数の傾きが変化する点の集合(多重集合)として管理するデータ構造です。
`std::priority_queue` を2つ用いることで、特定の関数の加算やスライド最小値更新を高速に処理できます。

## `slope_trick`

```cpp
template<class T, T MAXVALUE = numeric_limits<T>::max() / 2>
struct slope_trick;
```

### メンバ変数
- `T min_value`: 現在の関数の最小値
- `T Loffset`: 左側の傾き変化点全体にかかる平行移動のオフセット
- `T Roffset`: 右側の傾き変化点全体にかかる平行移動のオフセット

### メソッド

- `slope_trick()`
  $f(x) = 0$ (常に $0$) で初期化します。

- `T get_ltop()`
  左側（傾きが $0$ 以下から変化する部分）の最大の $x$ 座標を返します。集合が空の場合は `-MAXVALUE` を返します。

- `T get_rtop()`
  右側（傾きが $0$ 以上に変化する部分）の最小の $x$ 座標を返します。集合が空の場合は `MAXVALUE` を返します。

- `void add_R(T a)`
  関数に $\max(x - a, 0)$ を加算します。つまり、$x \ge a$ の範囲で傾きを $+1$ します。
  計算量: $O(\log N)$

- `void add_L(T a)`
  関数に $\max(a - x, 0)$ を加算します。つまり、$x \le a$ の範囲で傾きを $-1$ します。
  計算量: $O(\log N)$

- `void add_both(T a)`
  関数に $|x - a|$ すなわち $\max(a - x, 0) + \max(x - a, 0)$ を加算します。
  計算量: $O(\log N)$

- `void slide_min(T L, T R)`
  関数を $g(x) = \min_{x - R \le a \le x - L} f(a)$ に更新します。
  これは関数の平坦な部分(最小値を取る区間)を左に $L$、右に $R$ 拡張することに相当します。
  計算量: $O(1)$
