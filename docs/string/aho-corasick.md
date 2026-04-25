---
title: Aho-Corasick
documentation_of: ../../string/aho-corasick.hpp
---

# Aho-Corasick

複数パターンをまとめて trie に入れ、suffix link を張ったオートマトンです。
複数文字列の出現判定、出現回数集計、suffix link tree 上の DP などに使えます。

## 使い方

```cpp
#include "string/aho-corasick.hpp"

auto f=[](char c){ return c-'a'; };
AhoCorasick<26,f> ac;

string a="he";
string b="she";
string c="hers";
ac.add(a);
ac.add(b);
ac.add(c);
ac.build();
```

各ノードで遷移しながら文字列を読む基本形は次の通りです。

```cpp
int v=ac.root;
string text="ushers";
for(char ch:text){
    int x=f(ch);
    while(v!=ac.root&&ac.child[v][x]==-1)v=ac.suffix[v];
    if(ac.child[v][x]!=-1)v=ac.child[v][x];
}
```

## メンバ

- `child`
  trie の遷移です。存在しない遷移は `-1` です。
- `suffix`
  suffix link です。
- `depth`
  trie 上での深さです。
- `word`
  `add` した文字列の終端ノード一覧です。追加順に push されます。
- `root`
  根ノードです。

## メソッド

- `int add(String& s)`
  文字列 `s` を trie に追加します。
  新規に作られたノード数を返します。

- `void build()`
  suffix link を BFS で構築します。

- `int size()`
  ノード数を返します。

- `vc<int> suffix_order()`
  suffix link tree で親から子へ流す DP に使いやすい順序を返します。

- `vvc<int> suffix_inv()`
  suffix link tree の子リストを返します。

## 典型例

出現回数を suffix link tree で集約する流れは次の形です。

1. text を読んで各訪問ノードのカウントを増やす
2. `suffix_order()` の逆向きや `suffix_inv()` を使って suffix link 親へ集約する
3. `word[i]` を見れば i 番目に追加した文字列の終端ノードが分かる

## 注意

- `give_order` は文字を `0...sigma-1` に写す関数です。
- `build()` 前に `suffix` を使うことはできません。
