---
title: two_satisfiability
documentation_of: ../../graph/two-sat.hpp
---

# two_satisfiability

2-SAT を解くための構造体です。
変数 `i` ごとに真偽値を 1 つ持ち、OR 節や含意を追加して充足可能性を判定します。

## コンストラクタ

### `two_satisfiability(int n)`

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

### `void sat.lessthan(vc<int> v, vc<int> op)`

各 `i` についてリテラル `(x_v[i]=bool(op[i]))` を作り、そのうち高々 1 個だけが真になる制約を逐次カウンタで追加します。内部補助変数を `v.size()-1` 個追加します。

- 制約: `v.size()==op.size()`、各変数番号が有効範囲内
- 計算量: `O(v.size())`

### `int sat.get_new()`

新しい変数を 1 個追加し、その番号を返します。

- 計算量: amortized `O(1)`

### `bool sat.satisfiable()`

充足可能なら `true`、不可能なら `false` を返します。
内部で SCC 分解を行います。

### `vc<int> sat.answer()`

一つの解を返します。
各要素は `0/1` です。
未計算なら内部で `satisfiable()` 相当の計算を行います。

## 計算量

- 節追加: `O(1)`
- `satisfiable()`, `answer()`: 逆隣接リストの列挙が次数に比例するグラフなら `O(n+m)`

ここで `m` は追加した含意辺数です。

内部の現行 `static_graph` では `inv(u)` ごとに逆 CSR を再構築するため、そのままのコードに対する最悪時間は `O(n(n+m))` です。保持領域は `O(n+m)`、再帰スタックは `O(n)` です。

## 境界・注意

- 変数番号は 0-indexed で、各 API に渡す番号はその時点の `0<=i<n` が必要です。
- すべての制約と補助変数を追加してから、初回の `satisfiable()` または `answer()` を呼んでください。SCC 計算時に内部 CSR が構築されるため、その後の制約追加は `assert` に失敗します。
- `answer()` 自体も未計算なら解きますが、充足不能時の `ans` 内容は解ではありません。先に `satisfiable()` の戻り値を確認してください。
- 変数 `i` の値は `answer()[i]` に入ります。
- `lessthan` という名前ですが、追加するのは数値の大小制約ではなく「指定リテラルのうち高々 1 個」です。空列・1 要素列には何も追加しません。

## 使用例

```cpp
#include "graph/two-sat.hpp"

two_satisfiability sat(n);
sat.add_clause(0,true,1,false); // x0 or !x1
sat.if_then(2,true,3,true);     // x2 => x3
sat.set_value(4,false);         // !x4

if(sat.satisfiable()){
    auto ans=sat.answer();
}
```
