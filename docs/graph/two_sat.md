---
title: TwoSatisfiability
documentation_of: ../../graph/two_sat.hpp
---

# TwoSatisfiability

2-SAT を解くための構造体です。
変数 `i` ごとに真偽値を 1 つ持ち、OR 節や含意を追加して充足可能性を判定します。

## コンストラクタ

### `TwoSatisfiability(int n)`

変数数 `n` で初期化します。

## メソッド

### `void sat.add_clause(int a, bool fa, int b, bool fb)`

節

`(x_a = fa) OR (x_b = fb)`

を追加します。

### `void sat.if_then(int a, bool fa, int b, bool fb)`

含意

`(x_a = fa) => (x_b = fb)`

を追加します。

### `void sat.set_value(int a, bool fa)`

`x_a = fa` を強制します。

### `bool sat.satisfiable()`

充足可能なら `true`、不可能なら `false` を返します。
内部で SCC 分解を行います。

### `vc<int> sat.answer()`

一つの解を返します。
各要素は `0/1` です。

## 使用例

```cpp
#include "graph/two_sat.hpp"

TwoSatisfiability sat(n);
sat.add_clause(0,true,1,false); // x0 or !x1
sat.if_then(2,true,3,true);     // x2 => x3
sat.set_value(4,false);         // !x4

if(sat.satisfiable()){
    auto ans=sat.answer();
}
```

## 計算量

- 節追加: `O(1)`
- `satisfiable()`: `O(n+m)`

ここで `m` は追加した含意辺数です。

## 注意

- `answer()` は `satisfiable()` を呼んだあとに使う想定です。
- 変数 `i` の値は `answer()[i]` に入ります。
