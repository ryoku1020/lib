---
title: EerTree
documentation_of: ../../string/eer-tree.hpp
---

# EerTree

回文部分文字列を管理する木構造です。
文字列を左から 1 文字ずつ追加しながら、その時点での最長回文接尾辞や新しく増えた回文を追えます。

## 使い方

```cpp
#include "string/eer-tree.hpp"

EerTree<26> et;
et.build("abacaba",'a');
```

## 主なメンバ

- `len[v]`
  ノード `v` が表す回文の長さです。
- `suffix[v]`
  その回文の最長真回文接尾辞へのリンクです。
- `child[v][c]`
  文字 `c` を両端に付けてできる回文への遷移です。
- `pali_node[i]`
  `s[0..i]` を見た時点での最長回文接尾辞を表すノードです。

## `build`

- `void build(string s,char CHRMIN)`
  文字列 `s` から EerTree を構築します。
  各文字は `s[i]-CHRMIN` で `0...sigma-1` に写る必要があります。

## 典型的な見方

```cpp
string s="abacaba";
EerTree<26> et;
et.build(s,'a');

for(int i=0;i<s.size();i++){
    int node=et.pali_node[i];
    int len=et.len[node];
    // s[0..i] の最長回文接尾辞の長さが len
}
```

## 注意

- 内部には長さ `-1` と `0` の 2 つの根ノードがあります。
- `build` は英小文字のように連続した alphabet を想定しています。
