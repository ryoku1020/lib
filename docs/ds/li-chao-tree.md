---
title: LiChaoTree
documentation_of: ../../ds/li-chao-tree.hpp
---

# LiChaoTree

Li Chao Tree です。
`[0, n)` の整数 x 座標に対して、直線（または線分）の追加と、指定した x での最小値（または最大値）クエリを `O(log n)` で行えます。

座標範囲が固定でよい場合はこれを使ってください。
座標が大きい・実数の場合は [DynamicLiChaoTree](dynamic-li-chao-tree.md)、
クエリ座標が事前にわかっている場合は [CompressedLiChaoTree](compressed-li-chao-tree.md) が使えます。

## 要件: `Info`

```cpp
struct Info {
    using value_type = /* 直線を表す型 */;
    static value_type e();                        // 番兵（初期値）。eval で inf を返す直線
    static auto eval(value_type line, auto x);    // 直線 line の x における値
};
```

`Info::eval` が大きい値を返すほど「弱い」直線として扱います。
`ismin=true` なら最小値を返し、`ismin=false` なら最大値を返します。

### `Info` の例: `ax + b` の最小値クエリ

```cpp
struct Info {
    using value_type = pair<long long, long long>; // {a, b}
    static value_type e() { return {0, (long long)4e18}; }
    static long long eval(value_type line, long long x) {
        return line.first * x + line.second;
    }
};
using LCT = LiChaoTree<Info, true>;
```

## コンストラクタ

### `LiChaoTree(int n)`

x 座標の範囲 `[0, n)` で Li Chao Tree を作ります。

- 計算量: `O(n)`

## メソッド

### `void lct.add_line(Line a)`

直線 `a` を全体に追加します。

- 計算量: `O(log n)`

### `void lct.add_segment(Line a, int l, int r)`

x ∈ `[l, r)` の範囲にのみ有効な線分 `a` を追加します。

- 制約: `0 <= l <= r <= n`
- 計算量: `O(log^2 n)`

### `T lct.query(T x)`

x における最小値（`ismin=true`）または最大値（`ismin=false`）を返します。

- 制約: `0 <= x < n`
- 計算量: `O(log n)`

## 使用例: CHT（Convex Hull Trick）

直線 `y = ax + b` の `x ∈ [0, N)` での最小値を管理します。

```cpp
#include "ds/li-chao-tree.hpp"

struct Info {
    using value_type = pair<long long, long long>;
    static value_type e() { return {0, (long long)4e18}; }
    static long long eval(value_type f, long long x) {
        return f.first * x + f.second;
    }
};

LiChaoTree<Info, true> lct(N);

lct.add_line({a, b}); // y = ax + b を追加
long long ans = lct.query(x);
```

## 注意

- x 座標は整数で `[0, n)` の範囲です。
- `Info::e()` が返す直線は `eval` 時に `inf` を返す番兵として使われます。最小値クエリなら `4e18`、最大値クエリなら `-4e18` などを返すようにしてください。
- 内部的には n を 2 のべき乗に切り上げています。
