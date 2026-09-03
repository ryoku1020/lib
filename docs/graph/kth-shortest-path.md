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
  到達不能またはそれ以上のパスが存在しない場合、対応する位置は `T(-1)`。

- 制約: `0<=s<n`, `0<=t<n`, `k>0`、辺重みは非負

## 計算量

`g[u]`, `g.inv(u)` の全走査がそれぞれ次数に比例すると仮定すると、`O((N+M)log N+M log(M+1)+K log K)` 時間です。永続 leftist heap のノードを `new` で確保するため、領域は `O(M log(M+1)+K)` が上界です。

現行の `static_graph` は `inv(u)` のたびに逆 CSR を再構築するため、それを `G` に使った場合の実時間には `O(N(N+M))` が加わります。

## 境界・注意

- `g.inv(v)` が使えるグラフ型を仮定しています。現行の型名は `graph/base.hpp` の `static_graph` です。
- 実装が `.hpp` ではなく `.cpp` にあります。`#include "graph/kth-shortest-path.cpp"` で読み込みます。
- Dijkstra 法で終点からの距離を作るため、負辺には対応していません。
- 列挙対象は単純路に限定されず、頂点や辺を繰り返す walk を含みます。閉路があれば同じ頂点を再訪する候補も列挙されます。
- 候補が不足した位置は `-1` で埋めるため、`T` は `-1` を表現できる型にしてください。
- 辺 ID を `used` 配列の添字にするため、全元辺の ID は `0,1,...,M-1` の連番かつ一意である必要があります。
- 実装の `assert` は `k>=0` ですが、`k==0` かつ `s` から `t` へ到達可能な場合は内部の `k` が負になって終了しません。必ず `k>0` としてください。
- `s==t` のとき「長さ 0 のパス（自己ループなし）」は経路として数えられます。
- heap ノードは関数終了時に解放されません。同じプロセスで何度も大規模入力に呼ぶ場合はメモリ使用量に注意してください。

## 使用例

```cpp
#include "graph/kth-shortest-path.cpp"

// g は inv() が使える非負重み付き有向グラフ
auto ds = kthshortestpath<long long>(g, s, t, k);

for(int i=0;i<k;i++){
    if(ds[i] == -1){
        // i+1 番目のパスは存在しない
    } else {
        cout << ds[i] << "\n";
    }
}
```
