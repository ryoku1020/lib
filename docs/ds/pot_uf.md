---
title: PotentializedUnionFind
documentation_of: ../../ds/pot_uf.hpp
---

# PotentializedUnionFind

重み付き Union-Find です。
各頂点の「ポテンシャル差」をグループ管理します。

内部では `val[x]` という仮想的な重みを持ち、辺 `(x,y,W)` は `val[x] = val[y] * W` という条件を表します。

## 要件

```cpp
struct X {
    using value_type = ...;
    static value_type op(value_type a, value_type b); // a*b（モノイド積）
    static value_type inv(value_type a);               // a^{-1}（逆元）
    static value_type e();                             // 単位元
};
```

群（逆元が存在するモノイド）を定義する必要があります。

### 例：加法群（整数の差分管理）

```cpp
struct X {
    using value_type = long long;
    static value_type op(value_type a, value_type b) { return a + b; }
    static value_type inv(value_type a) { return -a; }
    static value_type e() { return 0; }
};
```

この場合 `val[x] - val[y]` が管理できます。

## コンストラクタ

### `PotentializedUnionFind<X>(int n)`

要素数 `n` で初期化します。初期状態では全要素が独立した成分です。

## メソッド

### `int uf.root(int x)`

`x` が属する成分の代表元を返します。

- 制約: `0<=x<n`
- 計算量: ならし `O(alpha(n))`

### `bool uf.same(int x, int y)`

`x` と `y` が同じ成分なら `true`、異なれば `false` を返します。

- 計算量: ならし `O(alpha(n))`

### `value_type uf.diff(int x, int y)`

`val[x]^{-1} * val[y]` を返します（加法群なら `val[y] - val[x]`）。

- 制約: `same(x, y) == true`（異なる成分で呼ぶと `assert` で停止）
- 計算量: ならし `O(alpha(n))`

### `int uf.merge(int x, int y, value_type W)`

`val[x] = val[y] * W` となるよう併合します。

- 返り値:
  - `1` — 新規に併合した
  - `0` — すでに同じ成分で、条件が矛盾しない
  - `-1` — すでに同じ成分だが、既存の重みと矛盾する
- 計算量: ならし `O(alpha(n))`

## 使用例：各クエリで「差が W」という条件を追加

```cpp
#include "ds/pot_uf.hpp"

// 加法群（差分 val[y] - val[x] = W を管理）
struct X {
    using value_type = long long;
    static value_type op(value_type a, value_type b) { return a + b; }
    static value_type inv(value_type a) { return -a; }
    static value_type e() { return 0; }
};

PotentializedUnionFind<X> uf(n);

// val[y] - val[x] = 5 という条件を追加
int res = uf.merge(x, y, 5);
if (res == -1) {
    // 矛盾: 既存の条件と違う
}

// 条件を満たす割り当てが存在する場合、差分を取得
if (uf.same(x, z)) {
    long long d = uf.diff(x, z); // val[z] - val[x]
}
```

## 注意

- `diff(x, y)` は `same(x, y)` のときのみ呼べます。異なる成分で呼ぶと `assert` で停止します。
- `op` は群の演算（逆元が存在するモノイド）である必要があります。
