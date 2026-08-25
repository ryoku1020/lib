---
title: dynamic_li_chao_tree
documentation_of: ../../ds/li_chao_tree/dynamic-li-chao-tree.hpp
---

# dynamic_li_chao_tree

動的ノード割り当て版の Li Chao tree です。
x 座標の型を任意にとれるため、x が大きい整数・負の値のときや、全 x 範囲 `[0, n)` の中でクエリが疎なときに有効です。

ノードが必要になった時点だけ `new` で確保するため、空間計算量はクエリ・直線追加の数に比例します。

x 座標が事前にわかっている場合は [compressed_li_chao_tree](compressed-li-chao-tree.md) の方が定数倍が小さいです。

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

### `dynamic_li_chao_tree(T n)`

x 座標の範囲 `[0, n)` で動的 Li Chao tree を作ります。
内部では `n` を 2 のべき乗に切り上げます。

- `T` は x 座標の型（`int`, `long long` など）
- 計算量: `O(1)`

## メソッド

### `void lct.add_line(Line a)`

直線 `a` を全体に追加します。

- 計算量: `O(log n)`（ノード確保含む）

### `void lct.add_segment(Line a, T ql, T qr)`

x ∈ `[ql, qr)` の範囲にのみ有効な線分 `a` を追加します。

- 制約: `0 <= ql <= qr <= n`
- 計算量: `O(log^2 n)`

### `auto lct.query(T x)`

x における最小値（`ismin=true`）または最大値（`ismin=false`）を返します。

- 制約: `0 <= x < n`
- 計算量: `O(log n)`

## 境界・注意

- `eval` は `ismin` の場合でも常に「大きい値を返すほど弱い」設計になっています（コンストラクタで `coef` による符号反転はクエリ時のみ適用）。コメントにも `"max で eval される"` と書かれています。
- ノードのデストラクタが再帰的に `delete` を呼ぶため、非常に深いツリーではスタックオーバーフローの可能性があります。
- [li_chao_tree](li-chao-tree.md) と違い x 座標は `T` 型なので、`int` 範囲外の座標も扱えます。

## 使用例

```cpp
#include "ds/li_chao_tree/dynamic-li-chao-tree.hpp"

struct info {
    using value_type = pair<long long, long long>;
    static value_type e() { return {0, (long long)4e18}; }
    static long long eval(value_type f, long long x) {
        return f.first * x + f.second;
    }
};

// x ∈ [0, 1e18) の範囲で最小値クエリ
dynamic_li_chao_tree<info, true, long long> lct(1e18);

lct.add_line({a, b});
long long ans = lct.query(x);
```
