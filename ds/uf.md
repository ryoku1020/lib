---
title: UnionFind (dsu / extra_dsu)
documentation_of: ./uf.cpp
---

# UnionFind (dsu / extra_dsu)

素集合データ構造 (Union-Find / Disjoint Set Union) です。経路圧縮とサイズによるマージを用いており、要素の併合と連結判定をならし $O(\alpha(N))$ で行います。
また、各連結成分ごとにモノイドを載せることができる `extra_dsu` も提供しています。

## `dsu` (通常のUnion-Find)

要素を連結成分にまとめ、それぞれの属するグループを管理します。

### 使い方

```cpp
#include "ds/uf.cpp"

// 頂点数 N で初期化
dsu uf(N);

// 頂点 x と y を併合
uf.merge(x, y);

// 頂点 x と y が同じ連結成分か判定
bool b = uf.same(x, y);

// 頂点 x が属する連結成分のサイズ
int s = uf.size(x);
```

### 計算量・メソッド
- `dsu(int n)`: 要素数 $n$ で初期化。$O(n)$
- `bool merge(int x, int y)`: 頂点 $x, y$ の属する成分を併合します。すでに同じ成分に属していた場合は `false`、新たに併合した場合は `true` を返します。ならし $O(\alpha(N))$
- `bool same(int x, int y)`: 頂点 $x, y$ が同じ成分に属しているか判定します。ならし $O(\alpha(N))$
- `int root(int x)` (または `leader(int x)`): 頂点 $x$ の属する成分の代表元を返します。ならし $O(\alpha(N))$
- `int size(int x)`: 頂点 $x$ の属する成分の頂点数を返します。ならし $O(\alpha(N))$
- 制約: 頂点のインデックスは全て $0 \le x, y < n$ の閉区間（配列のインデックス）です。

## `extra_dsu` (データ付きUnion-Find)

連結成分の併合時に、成分ごとに持たせたデータを二項演算 `op` でマージします。

### 使い方

```cpp
#include "ds/uf.cpp"

// 頂点成分に持たせるデータ型と併合演算を定義
long long op(long long a, long long b) { return a + b; }

// 頂点数 N, 初期値 0 で初期化
extra_dsu<long long, op> uf(N, 0);

// 初期値の代入 (代表元を介してアクセス)
uf[0] = 10;
uf[1] = 20;

// 頂点を併合。演算 op によってデータも併合される (この例では和が取られる)
uf.merge(0, 1);

// 併合後の成分のデータにアクセス
long long sum = uf[0]; // 30
```

### 計算量・メソッド
通常の `dsu` に加えて以下の機能が追加されています。
- `extra_dsu(int n, T e)`: 要素数 $n$、初期値 `e` で初期化します。$O(n)$
- `T& operator[](int i)`: 頂点 $i$ が属する連結成分のデータへの参照を返します。代入も可能です。ならし $O(\alpha(N))$
- `merge(int x, int y)` 時に、`data[x_root] = op(data[y_root], data[x_root])` となるようにデータが併合されます（サイズが大きかった方の代表元が新たな代表元となります）。ならし $O(\alpha(N))$
