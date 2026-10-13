---
title: rectadd_pointsum
documentation_of: ../../ds/range_queries/rectadd-pointsum.hpp
---

# rectadd_pointsum

長方形への加算と点の値の取得を、座標圧縮・スイープライン・Fenwick tree でオフライン処理します。

```cpp
#include "ds/range_queries/rectadd-pointsum.hpp"

rectadd_pointsum<ll>rs;
rs.add_rect(0,3,0,2,5);
rs.add_rect(1,4,1,3,2);
rs.add_query(1,1);
rs.add_query(3,1);
auto ans=rs.work(); // {7,2}
```

- `add_rect(l,r,d,u,w)` は `[l,r) × [d,u)` に重み `w` を加える長方形を登録します。`l<=r`, `d<=u` とし、空の長方形も登録できます。
- `add_query(x,y)` は点 `(x,y)` を登録します。
- `work()` は登録したすべての長方形による値を、クエリの登録順に `vc<T>` で返します。登録した順序にかかわらず、すべての長方形がすべてのクエリに適用されます。
- 座標は `ll` で、負の座標にも対応します。重みの型 `T` は `0` からの初期化、加算、単項マイナスをサポートする必要があります。
- `work()` は登録済みの座標を変更しません。再実行や追加登録後の再実行もできます。
- `work()` は `const` で、クエリの x 座標だけを圧縮し、y 座標順にイベントを処理します。空または逆転した長方形は無視します。
- 長方形数を `n`、クエリ数を `q` とすると、`work()` の時間計算量は `O((n+q) log(n+q))`、空間計算量は `O(n+q)` です。
