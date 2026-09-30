---
title: テストデータ生成・全列挙 | generator
documentation_of: ../../misc/generator/generator.hpp
keywords: randomgraph, randomtree, randomsequence, enumeratesequence, generator_engine
---

# テストデータ生成・全列挙

乱択テストや小さい状態空間の総当たり用ユーティリティです。`generator.hpp` を include すると一式が使えます。

```cpp
#include "misc/generator/generator.hpp"

auto edges = randomtree(n);             // n-1 辺の木
auto graph = randomgraph(n, m, true);   // 連結単純無向グラフ
auto a = randomsequence(n, 10);         // [0,10) の整数列
for (auto x : enumeratesequence(3, 2)) { // 000..111
    /* x は vector<int> */
}
```

- `randomtree(n)` は頂点 `0..n-1` の無向木を辺ペアの vector で返す。`n<=1` は空。親候補 `0..i-1` から各頂点 `i` を接続するので連結・非巡回。`O(n)`。
- `randomgraph(n,m,connected=false)` は自己ループ・重複辺のない単純無向グラフを返す。各辺 `{u,v}` は `u<v`。`connected=true` は連結にするため `m>=n-1` が必要（`n==0` は例外扱い）。実行時間は疎密に応じ、密な場合に候補辺を列挙して shuffle する。
- `randomsequence(n,m)` は `[0,m)` の整数 `n` 個。`n>0` なら `m>0`。要素は一様乱数だが、シード未固定なら再現性はありません。
- `enumeratesequence(n,m)` は長さ `n`、各要素 `[0,m)` の vector を辞書順相当で列挙します。要素数 `m^n`。`n==0` の場合も range-for は空列を 1 個列挙します。
- `generator_engine()` は全乱択関数が共有する `mt19937_64&`。再現テストでは最初に `generator_engine().seed(seed)` を呼びます。

乱択関数は競技本番のアルゴリズムには使わず、ローカルテストや stress test 用です。`enumeratesequece`（綴り違い）も同じ `enumeratesequence` を返す互換関数です。
