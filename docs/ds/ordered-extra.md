---
title: 順序付き区間集合・Hash Map | range_set / hashmap
documentation_of: ../../ds/ordered/hashmap.hpp
keywords: hashmap, hash map, range_set, range_set_info, insert, erase, contains, enumerate
---

# 順序付き区間集合・Hash Map

## Hash Map (`hashmap<Key,Val,tohash>`)

線形探索法の自前 Hash Map です。`std::unordered_map` 風に `operator[]` で値を取得・挿入します。

```cpp
#include "ds/ordered/hashmap.hpp"

hashmap<long long, long long> mp;
mp[10] += 3;             // 未登録なら値を既定構築して挿入
if (mp.count(10)) { /* 存在する */ }
mp.erase(10);
```

- `operator[](key)` は参照を返し、未登録キーなら既定構築された `Val` を挿入。`O(1)` 期待（再ハッシュ時 `O(n)`）。
- `count(key)` は 0/1、`erase(key)` は削除成功なら 1、なければ 0。`size()`, `empty()`, `clear()`, `reserve(n)` もある。
- `for (auto& [key,value] : mp)` 相当の range-for は `Node{k,v}` を列挙する。API は `Node::k`, `Node::v`。
- `Key` は `tohash` が受け取れる型で、現在の既定 `hashmap_hash` は `ull` に変換できる整数キー向けです。任意の文字列キーを `std::hash` のように自動処理しません。
- 乱数 seed 付き hash による線形探索で、操作時間は期待 `O(1)`、メモリ `O(cap)`。キーの hash 値が悪い場合の最悪時間は `O(n)`。
- `reserve(S)` は少なくとも S 要素を load factor 0.5 以下で保持できる容量を確保します。参照は再ハッシュで無効になります。

## 区間の和集合 (`range_set<T>`)

互いに交差しない半開区間の集合を `std::set` で管理します。

```cpp
#include "ds/ordered/range-set.hpp"

range_set<long long> rs;
rs.insert(2, 7);        // [2,7)
rs.insert(6, 9);        // 隣接・重複区間は [2,9) に併合
bool b = rs.contains(4, 8);
auto parts = rs.enumerate(5, 10); // {{5,9}}
rs.erase(3, 6);
```

- `insert(l,r)` は `[l,r)` を追加し、重なる区間・端で隣接する区間を併合します。空区間は no-op。
- `erase(l,r)` は `[l,r)` と交わる箇所だけを削除し、はみ出した部分は残します。
- `contains(x)` は点を含むか、`contains(l,r)` は区間全体が被覆されるか。空区間は `true`。
- `find(x)` は `x` を含む区間 iterator、なければ `st.end()`。`lower_bound(x)` は x を含む区間または次の区間。
- `enumerate(l,r)` は交差部分を `{max(l,a),min(r,b)}` の vector で返す。
- `covered` は集合が被覆する長さの合計。整数格子上の個数ではなく端点差の総和です。
- `insert` / `erase` は触れる区間数を `k` として `O((k+1) log n)`、検索だけなら `O(log n)`。

## 区間ごとの monoid 値 (`range_set_info<T,Info>`)

区間ごとに値を持ち、`apply(l,r,x)` で情報を重ねます。未登録区間の値は `Info::e()` です。

- `Info` は `value_type`, `op(a,b)`, `e()` を持つ。
- `apply(l,r,x)` は `[l,r)` に `Info::op(既存値,x)` を適用します。`op` が非可換ならこの順序が意味を持ちます。`x==e()` と空区間は no-op。
- `get(l,r)` は範囲を全て覆う `{区間左,区間右,value}` の tuple 列を返し、隣接する同じ値は結果上まとめます。範囲外の未登録部分も `e()` として返します。
- 内部 set のノード数を `n`、更新で交わる区間数を `k` として `apply` / `get` は `O((k+1) log n)` を目安とします。更新で区間分割数は増加し得ます。

## 整数 trie (`Trie<sigma>`)

`Trie<sigma>` は各記号を `[0,sigma)` に写した列を node pool の trie に登録します。

```cpp
#include "ds/trie.hpp"

Trie<26> tr;
tr.insert({0, 1, 2}, 1); // 文字列 "abc" を 1 個追加
int count = tr.size();   // 登録した重みの合計
```

- `insert(vc<int> v,int size)` は列 `v` の全 prefix node の `cnt` に `size` を加算します。`size` は負でも受け入れますが、個数を表すなら非負を渡します。
- `size()` は root の `cnt`、つまり挿入重み合計。終端専用の検索・個数取得 API はありません。
- 各 `v[i]` は `[0,sigma)` が必須ですが、実装に assert はありません。
- 長さ `L` の追加は `O(L)` 時間・新規 node 数に比例する領域。`node_pool` の寿命・確保量制約は [node_pool](node-pool.md) を参照。

関連: 多重集合と XOR 検索なら [binary trie](binary-trie.md)、重複なし順序集合なら [set treap](setreap.md)、区間区切りならこの `range_set`。
