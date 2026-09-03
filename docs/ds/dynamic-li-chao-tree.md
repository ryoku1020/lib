---
title: dynamic_li_chao_tree
documentation_of: ../../ds/li_chao_tree/dynamic-li-chao-tree.hpp
---

# dynamic_li_chao_tree

動的ノード割り当て版の Li Chao tree です。
x 座標の型 `T` を指定できるため、x が大きい非負整数のときや、全 x 範囲 `[0,n)` の中でクエリが疎なときに有効です。

ノードが必要になった時点だけ `new` で確保します。クエリはノードを生成しません。

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
- 制約: `n>=0`
- 計算量: `O(log max(1,n))`（2 冪への切り上げ）

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

- `T` には比較、加減算、整数の `>>` が使える型が必要です。負数・実数座標には対応せず、範囲は `[0,n)` です。
- ノードのデストラクタが再帰的に `delete` を呼ぶため、非常に深いツリーではスタックオーバーフローの可能性があります。
- [li_chao_tree](li-chao-tree.md) と違い x 座標は `T` 型なので、`int` 範囲外の座標も扱えます。
- 現在の実装は `ismin=false` の `query` で候補値に `coef` を掛けず `chmin` しているため、通常の `eval(line,x)` を与えた最大値モードは正しい最大値になりません。最大値が必要なら、修正されるまでは `ismin=true` で直線と答えの符号を反転するか、静的版・圧縮版を使ってください。

## 空間計算量

直線追加は `O(log n)`、線分追加は `O(log^2 n)` 個までノードを生成します。`A` 回の直線追加と `S` 回の線分追加後の空間は `O(A log n+S log^2 n)`、クエリによる追加確保はありません。

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
