---
title: contour_add
documentation_of: ../../tree/contour.hpp
---

# contour_add

木上の各頂点に値を持たせ、ある頂点から距離制約付きで和を取るための構造体です。
内部では `centroid_decomposition13` と `binary_indexed_tree` を使って、更新と距離範囲クエリを処理します。

## `contour_add<T>`

### 使い方

```cpp
#include "tree/centroid.hpp"
#include "tree/contour.hpp"

tree tree(n);
// 辺を追加

vector<long long> init(n);
contour_add<long long> ds(tree);
ds.work(init);

long long within_r=ds.prod(v,r);
long long in_lr=ds.prod(v,l,r);

ds.add(v,x);
```

「頂点 `v` から距離 2 以下にある頂点重みの総和」を何度も聞かれる問題を想定すると、次のように使えます。

```cpp
tree tree(n);
// 辺を追加

vector<long long> a(n);
contour_add<long long> ds(tree);
ds.work(a);

long long ans=ds.prod(v,3); // 距離 0,1,2 の総和
ds.add(v,5);                // a[v]+=5
```

### コンストラクタ

- `contour_add(tree& tree)`
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

## 計算量

頂点数を $N$ とします。

- `work`: `O(N log^2 N)` 時間、`O(N log N)` 領域
- `prod(v,r)`, `prod(v,l,r)`: `O(log^2 N)` 時間
- `add(v,x)`: `O(log^2 N)` 時間

各頂点は `O(log N)` 個の重心分解情報を持ち、それぞれで Fenwick Tree の `O(log N)` 操作を行います。

### 境界・注意

- `work` を呼ぶ前に `prod` や `add` を呼ぶことはできません。`work` は同じオブジェクトに対してちょうど 1 回だけ呼んでください。2 回目は内部の所属情報を消して早期 return する実装になっています。
- 現在の `work` の引数型はテンプレート引数 `T` によらず `vc<ll>&` です。また内部で `vc<T>` へ代入するため、実質的に `T=ll` での利用を想定しています。
- `tree/contour.hpp` は `centroid_decomposition13` を使いますが `tree/centroid.hpp` を直接 include しません。`all.hpp` を使わない場合は、使用例の順で `tree/centroid.hpp` も先に include してください。
- `first.size()==tree.size()` が必要ですが、実装内では検査されません。
- `0<=v<N`, `0<=l<=r<=N` が必要です。`prod(v,r)` は距離の半開区間 `[0,r)`、`prod(v,l,r)` は `[l,r)` を集計します。`r==0` の答えは 0 です。
- `prod` の距離は辺数で数え、重み付き木でも辺重みを無視します。
- 構築後に木構造を変更することは想定されていません。
- 加算と区間和を使うため、`T` には 0、加算、減算が必要です。
- 構造体名は実装に合わせて `contour_add` です。

## 使用例

頂点 `v` から距離 `K` 以下にある頂点値の総和を求めます。

```cpp
tree tree(n);
// 辺を追加

vc<long long> a(n);
contour_add<long long> contour(tree);
contour.work(a);

int v,K;
cin>>v>>K;

long long ans=contour.prod(v,K+1);
contour.add(v,3);
```
