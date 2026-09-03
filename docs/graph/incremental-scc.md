---
title: incremental_scc
documentation_of: ../../graph/connectivity/incremental-scc.hpp
---

# incremental_scc

有向辺を時系列に追加していったときの SCC マージをオフラインで処理する補助構造です。
かなり特殊用途寄りです。

## コンストラクタ

### `incremental_scc(int n = 0)`

頂点数 `n` で初期化します。

## メソッド

### `void inc.push(int a, int b)`

時刻順に辺 `a->b` を追加します。

- 制約: `0<=a,b<n`
- 計算量: amortized `O(1)`

### `vc<graph::edge> inc.work()`

内部処理を行い、マージ情報を返します。
返る `edge` の `id` には、そのマージが初めて起きた追加時刻（0-indexed）が入ります。
`from`, `to` はその時点で併合される DSU 代表であり、`push` した元辺を表すとは限りません。返された辺を時刻順に DSU へ適用すると、各時刻の SCC の併合を再現できます。

## 計算量

追加辺数を $M$ とします。各 SCC 呼び出しで逆隣接リストを次数に比例する時間で列挙できるグラフ実装なら、`work()` は `O(N+M log(M+1) alpha(N))` 時間、`O(N+M)` 補助領域です。ここで `alpha` は Union-Find の逆 Ackermann 関数です。

各分割統治段で、対象辺から縮約グラフを作って SCC を計算します。空の入力では `work()` は `O(1)` で空配列を返します（コンストラクタでの `O(N)` 初期化は別です）。

ただし現行コードが内部で使う `static_graph` は、`buildinv()` の完了フラグを設定しないため `inv(u)` ごとに逆 CSR を再構築します。この実装をそのまま評価した保守的な最悪上界は `O(N+M^2 log(M+1))` です。

## 境界・注意

- 一般用途の SCC ではなく、増加列に対する特殊なオフライン処理です。
- 辺の追加時刻は `push` の呼び出し順で `0,1,...` と振られます。同時刻に複数辺を追加する API はありません。
- `push` は頂点範囲を検査しないため、必ず `0<=a,b<n` を満たしてください。自己ループは登録できますが、SCC の併合イベントは発生させません。
- `work()` は内部の Union-Find、出力配列、辺順を破壊的に更新します。すべての辺を `push` してから 1 回だけ呼び、呼び出し後の追加や再実行はしないでください。
- 出力は SCC そのものの一覧ではなく、SCC が併合されるイベントを表す森です。各時刻の成分 ID が必要なら、出力を使って別途 Union-Find を更新してください。

## 使用例

辺を時刻順に登録し、SCC がマージされた時刻を取り出します。

```cpp
#include "graph/connectivity/incremental-scc.hpp"

incremental_scc inc(n);
for(auto [a,b]:edges){
    inc.push(a,b);
}

auto merges=inc.work();
for(auto e:merges){
    int u=e.from;
    int v=e.to;
    int time=e.id;
    // time 番目までの辺追加で u と v の SCC がマージされた
}
```
