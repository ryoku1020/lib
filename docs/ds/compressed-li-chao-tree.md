---
title: compressed_li_chao_tree
documentation_of: ../../ds/li_chao_tree/compressed-li-chao-tree.hpp
---

# compressed_li_chao_tree

座標圧縮版の Li Chao tree です。
クエリ対象の x 座標が事前にわかっている場合に使います。
`add_x` で x 座標を登録 → `build` で圧縮 → `add_line` / `query` の順に使います。

x 座標が `[0, n)` の整数なら [li_chao_tree](li-chao-tree.md)、
座標が事前にわからない大きい整数・実数なら [dynamic_li_chao_tree](dynamic-li-chao-tree.md) を使ってください。

## 要件: `info`

[li_chao_tree](li-chao-tree.md) の `info` と同じ仕様です。

```cpp
struct info {
    using value_type = /* 直線を表す型 */;
    static value_type e();
    static auto eval(value_type line, auto x);
};
```

## コンストラクタ

### `compressed_li_chao_tree(int n = 0)`

初期容量 `n` で作ります（`n=0` でも問題ありません）。

- 計算量: `O(1)`

## メソッド（使用順）

### 1. `void lct.add_x(T x)`

クエリに使う x 座標 `x` を登録します。
`build()` を呼ぶ前にすべての x を登録してください。

- 計算量: `O(1)` amortized

### 2. `void lct.build()`

登録した x 座標を圧縮してツリーを構築します。
2 回目以降の呼び出しは無視されます（冪等）。
`add_line` / `add_segment` / `query` を呼ぶ前に 1 度だけ呼んでください。

- 計算量: `O(m log m)`（m = 登録済み x の個数）

### 3. `void lct.add_line(Line a)`

直線 `a` を追加します。

- 計算量: `O(log m)`

### 3. `void lct.add_segment(Line a, T L, T R)`

x ∈ `[L, R)` の範囲にのみ有効な線分 `a` を追加します。
`L`, `R` は `add_x` で登録済みの値である必要があります。

- 制約: `L`, `R` が `add_x` で登録済み
- 計算量: `O(log^2 m)`

### 3. `T lct.query(T x)`

x における最小値（`ismin=true`）または最大値（`ismin=false`）を返します。
`x` は `add_x` で登録済みの値である必要があります。

- 制約: `x` が `add_x` で登録済み
- 計算量: `O(log m)`

## 境界・注意

- `build()` を呼ぶ前に `add_line` / `add_segment` / `query` を呼んでも内部で自動 `build()` が実行されます（`add_line_` の先頭で `build()` を呼ぶ設計）。ただし、`build()` 後に `add_x` を追加しても反映されないので、登録は必ず `build()` の前にまとめてください。
- 内部で `compresser<T>` を利用しています（`template.hpp`）。
- `add_segment` の `L`, `R` が `add_x` で登録されていない場合は `assert` で止まります。

## 使用例

DP の遷移 `dp[j] = min_{i<j}(a[i]*x[j] + b[i])` を CHT で高速化する例です。

```cpp
#include "ds/li_chao_tree/compressed-li-chao-tree.hpp"

struct info {
    using value_type = pair<long long, long long>;
    static value_type e() { return {0, (long long)4e18}; }
    static long long eval(value_type f, long long x) {
        return f.first * x + f.second;
    }
};

compressed_li_chao_tree<info, true, long long> lct;

// まず全クエリ x 座標を登録
for (int j = 0; j < N; j++) lct.add_x(X[j]);
lct.build();

// 直線追加・クエリ
lct.add_line({a[i], b[i]});
long long ans = lct.query(X[j]);
```
