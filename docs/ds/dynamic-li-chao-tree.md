---
title: dynamic_li_chao_tree
documentation_of: ../../ds/li_chao_tree/dynamic-li-chao-tree.hpp
---

# dynamic_li_chao_tree

動的ノード割り当て版の Li Chao tree です。
x 座標の型 `T` を指定できるため、x が大きい非負整数のときや、全 x 範囲 `[0,n)` の中でクエリが疎なときに有効です。

ノードが必要になった時点だけ `new` で確保します。クエリはノードを生成しません。

x 座標が事前にわかっている場合は [compressed_li_chao_tree](compressed-li-chao-tree.md) の方が定数倍が小さいです。

## テンプレート引数・直線型

`dynamic_li_chao_tree<Line,T,ismin>` と指定します。`T` は座標・評価値の型、`ismin` は最小値なら `true`（既定）、最大値なら `false` です。

`Line` は `T eval(T x)const` と `static Line id()` を持つ型です。
[li_chao_tree](li-chao-tree.md) の `chtline<T>` をそのまま渡せます。最大値モードでも `id()` を変更する必要はありません。
`query` は評価値を返し、有効な直線がない座標では最小値モードは `inf<T>`、最大値モードは `-inf<T>` を返します。評価値はこの範囲に収まるようにしてください。

## コンストラクタ

### `dynamic_li_chao_tree(T n)`

x 座標の範囲 `[0, n)` で動的 Li Chao tree を作ります。
内部では `n` を 2 のべき乗に切り上げます。

- `T` は座標・評価値の型（`int`, `long long` など）
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

### `T lct.query(T x)`

x における最小値（`ismin=true`）または最大値（`ismin=false`）を返します。

- 制約: `0 <= x < n`
- 計算量: `O(log n)`

## 境界・注意

- `T` には比較、加減算、整数の `>>` が使える型が必要です。負数・実数座標には対応せず、範囲は `[0,n)` です。
- ノードのデストラクタが再帰的に `delete` を呼ぶため、非常に深いツリーではスタックオーバーフローの可能性があります。
- [li_chao_tree](li-chao-tree.md) の座標範囲は `int` 型ですが、この実装の座標範囲は `T` 型なので、`int` 範囲外の座標も扱えます。

## 空間計算量

直線追加は `O(log n)`、線分追加は `O(log^2 n)` 個までノードを生成します。`A` 回の直線追加と `S` 回の線分追加後の空間は `O(A log n+S log^2 n)`、クエリによる追加確保はありません。

## 使用例

```cpp
#include "ds/li_chao_tree/dynamic-li-chao-tree.hpp"

// chtline は li_chao_tree のページにある定義を使用

// x ∈ [0, 1e18) の範囲で最小値クエリ
dynamic_li_chao_tree<chtline<long long>,long long,true> lct(1e18);

lct.add_line({a, b});
long long ans = lct.query(x);
```
