---
title: Trie | Trie<sigma>
documentation_of: ../../ds/trie.hpp
keywords: trie, Trie, prefix tree, 文字列集合
---

# Trie (`Trie<sigma>`)

記号を整数 `[0,sigma)` に写した列を trie に追加します。prefix ごとの累積重みを持ちます。探索・終端判定 API はなく、追加した prefix の数を追跡する部品です。

```cpp
#include "ds/trie.hpp"

Trie<26> tr;
tr.insert({0, 1, 2}, 1); // 1 個分を追加
int total = tr.size();   // 全追加重み
```

- `Trie<sigma>()` は root のみを作る。
- `insert(vc<int> v, int size)` は各 prefix node の `cnt` に `size` を加算。空列なら root のみ加算。長さ `L` に対して `O(L)`。
- `size()` は root の `cnt` を返す。`size` は負数も渡せるが、個数用途では減算後に負にならないようにする。
- 各要素は `[0,sigma)` が必要。実装に範囲 assert はない。
- node pool でメモリを確保し、明示的な erase・prefix count・文字列検索は提供しない。

列を文字列として検索するなら [Aho–Corasick](../string/aho-corasick.md)、整数の XOR 順序統計なら [binary trie](binary-trie.md) を使います。
