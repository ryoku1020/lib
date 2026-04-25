---
title: countour_add
documentation_of: ../../tree/contour.hpp
---

# countour_add

木上の各頂点に値を持たせ、ある頂点から距離制約付きで和を取るための構造体です。
内部では `centroid_decomposition13` と `BinaryIndexedTree` を使って、更新と距離範囲クエリを処理します。

## `countour_add<T>`

### 使い方

```cpp
#include "tree/contour.hpp"

Tree tree(n);
// 辺を追加

vector<long long> init(n);
countour_add<long long> ds(tree);
ds.work(init);

long long within_r=ds.prod(v,r);
long long in_lr=ds.prod(v,l,r);

ds.add(v,x);
```

「頂点 `v` から距離 2 以下にある頂点重みの総和」を何度も聞かれる問題を想定すると、次のように使えます。

```cpp
Tree tree(n);
// 辺を追加

vector<long long> a(n);
countour_add<long long> ds(tree);
ds.work(a);

long long ans=ds.prod(v,3); // 距離 0,1,2 の総和
ds.add(v,5);                // a[v]+=5
```

### コンストラクタ

- `countour_add(Tree& tree)`
  対象となる木を参照で保持します。

### メソッド

- `void work(vc<ll>& first)`
  初期値 `first` で構築します。`first.size()==tree.size()` を想定しています。
  初回呼び出し時にのみ前計算を行い、各頂点がどの重心分解成分に属するかを記録します。

- `T prod(int v,int r)`
  頂点 `v` から距離 `r` 未満にある頂点の値の総和を返します。
  実装上は半開区間の距離条件になっており、`r==0` のときは 0 を返します。

- `T prod(int v,int l,int r)`
  頂点 `v` からの距離が `l` 以上 `r` 未満である頂点の値の総和を返します。
  `prod(v,r)-prod(v,l)` で計算されます。

- `void add(int v,T x)`
  頂点 `v` の値に `x` を加算します。

### 制約・注意

- `work` を呼ぶ前に `prod` や `add` を呼ぶことはできません。
- `prod` の距離は辺数で数えます。
- 構築後に木構造を変更することは想定されていません。
- 構造体名は実装に合わせて `countour_add` です。
