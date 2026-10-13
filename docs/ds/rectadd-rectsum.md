---
title: rectadd_rectsum
documentation_of: ../../ds/range_queries/rectadd-rectsum.hpp
---

# rectadd_rectsum

長方形への加算と長方形内の総和をオフライン処理します。四隅の差分と、内部の `inner_rectadd_pointsum` が管理する 4 つの係数を使って積分値を計算します。

```cpp
#include "ds/range_queries/rectadd-rectsum.hpp"

rectadd_rectsum<ll>rs;
rs.add_w(0,3,0,2,5);
rs.add_w(1,4,1,3,2);
rs.add_query(0,4,0,3);
rs.add_query(1,3,1,2);
auto ans=rs.work(); // {42,14}
```

- `add_w(l,r,d,u,w)` は `[l,r) × [d,u)` に重み `w` を加える長方形を登録します。
- `add_query(l,r,d,u)` は `[l,r) × [d,u)` の総和のクエリを登録します。整数座標の各単位マスの値の和、または区分的に一定な値の面積積分を返します。
- `work()` は登録したすべての長方形による総和を、クエリの登録順に `vc<T>` で返します。登録順序にかかわらず、すべての更新がすべてのクエリに適用されます。
- 更新・クエリとも `l<=r`, `d<=u` とします。空の長方形にも対応します。
- 座標は `ll` で、負の座標にも対応します。内部の上限に `inf<ll>` を使うため、すべての座標を `inf<ll>` 未満にしてください。
- `T` は `0` からの初期化、加算、単項マイナス、`ll` との乗算をサポートする必要があります。整数型では係数・中間値・結果が収まる型を使ってください。`static_modint` も使えます。
- `work()` は登録内容を変更しません。再実行や追加登録後の再実行もできます。
- 更新数を `n`、クエリ数を `q` とすると、`work()` の時間計算量は `O((n+q) log(n+q))`、空間計算量は `O(n+q)` です。
