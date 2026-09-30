---
title: csr_graph | 移行案内
documentation_of: ../../graph/base.hpp
keywords: csr_graph, static_graph, CSR, グラフ
---

# `csr_graph` の移行案内

旧 `csr_graph` 型は現行リポジトリにありません。代わりに [`static_graph`](base.md) を使います。`static_graph<true,T>` は有向、`static_graph<false,T>` は無向グラフで、各 edge に `from`, `to`, `id`, `cost` を持ちます。

```cpp
#include "graph/base.hpp"

static_graph<true, long long> g(n);
g.add_edge(u, v, cost);
g.build();
for (auto e : g[u]) { /* e.to, e.cost, e.id */ }
```

`build()` 後は辺追加できません。現行 API は [グラフ基本型](base.md) を参照してください。
