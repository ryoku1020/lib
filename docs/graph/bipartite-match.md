---
title: BipartiteMatching
documentation_of: ../../graph/bipartite-match.hpp
---

# BipartiteMatching

Hopcroft-Karp 法による二部マッチングです。
左側 `l` 頂点、右側 `r` 頂点の二部グラフに対して最大マッチングを求めます。

## コンストラクタ

### `BipartiteMatching(int l, int r)`

左側サイズ `l`、右側サイズ `r` で初期化します。

## メソッド

### `void bm.add_edge(int a, int b)`

左頂点 `a` と右頂点 `b` の間に辺を追加します。

- 制約: `0<=a<l`, `0<=b<r`

### `vc<pii> bm.work()`

最大マッチングを求め、マッチした辺の集合を返します。
各要素は `{left,right}` です。

- 計算量: `O(E*sqrt(V))`

## メンバ

- `pm[a]`
  左頂点 `a` とマッチしている右頂点。未マッチなら `-1`
- `qm[b]`
  右頂点 `b` とマッチしている左頂点。未マッチなら `-1`

## 境界・注意

- 頂点番号は左側・右側それぞれで 0-indexed です。
- `work()` を再度呼ぶと、現在のマッチング状態を引き継いで続行する形になります。

## 使用例

```cpp
#include "graph/bipartite-match.hpp"

BipartiteMatching bm(L,R);
for(auto [a,b]:edges)bm.add_edge(a,b);

auto match=bm.work();
int sz=match.size();
```

マッチング相手を配列で見たいときは `work()` 後に `pm`, `qm` を参照できます。

```cpp
for(int a=0;a<L;a++){
    if(bm.pm[a]!=-1){
        // a is matched with bm.pm[a]
    }
}
```

