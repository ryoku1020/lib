---
title: kth-shortest-path
documentation_of: ../../graph/kth-shortest-path.cpp
---

# kth-shortest-path

`s` から `t` への k-shortest paths の長さを小さい順に `k` 個返します。
Eppstein 系のアルゴリズムで、内部で leftist heap を使っています。

## 関数

### `vc<T> kthshortestpath<T>(G g, int s, int t, int k)`

`s`→`t` への最短経路 top-k の距離を返します。

- `T` — 距離の型（`long long` など）
- `G` — `g.inv(v)` で逆辺を列挙できるグラフ型（`.to`, `.from`, `.cost`, `.id` フィールドが必要）
- 返り値: 長さ `k` の `vc<T>`。i 番目が `(i+1)` 番目に短い経路の距離。
  到達不能またはそれ以上のパスが存在しない場合、対応する位置は `numeric_limits<T>::max()`（= `-1` ではなく最大値）。

- 制約: `0<=s<n`, `0<=t<n`, `k>=0`
- 計算量: `O((n + m + k) log n)` 程度

## 境界・注意

- `g.inv(v)` が使えるグラフ型を仮定しています。`graph/base.hpp` の `Graph` が対応しています。
- 実装が `.hpp` ではなく `.cpp` にあります。`#include "graph/kth-shortest-path.cpp"` で読み込みます。
- 到達不能パスは `numeric_limits<T>::max()` で埋まります（`-1` ではありません）。
- `s==t` のとき「長さ 0 のパス（自己ループなし）」は経路として数えられます。

## 使用例

```cpp
#include "graph/kth-shortest-path.cpp"

// g は inv() が使えるグラフ（graph/base.hpp の Graph など）
auto ds = kthshortestpath<long long>(g, s, t, k);

for(int i=0;i<k;i++){
    if(ds[i] == numeric_limits<long long>::max()){
        // i+1 番目のパスは存在しない
    } else {
        cout << ds[i] << "\n";
    }
}
```

