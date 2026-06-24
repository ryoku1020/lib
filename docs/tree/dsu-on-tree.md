---
title: DSU on Tree
documentation_of: ../../tree/dsu-on-tree.hpp
---

# DSU on Tree

いわゆる Sack / DSU on Tree を行うための薄いラッパーです。
`Tree` の heavy-light 情報を利用して、light な部分木を先に捨て、heavy な部分木だけを保持する順で DFS を進めます。

## `DsuOnTree<Tree>`

### 使い方

```cpp
#include "tree/dsu-on-tree.hpp"

Tree tree(n);
// 辺を追加

DsuOnTree solver(tree);

auto add=[&](int v){
    // 頂点 v を現在のデータ構造に追加
};
auto query=[&](int v){
    // 頂点 v を根とする部分木について答えを確定
};
auto reset=[&](){
    // keep=0 の部分木を掃除
};

solver.run(add,query,reset);
```

部分木の色数を数えるような問題では次の形で使えます。

```cpp
vector<int> color(n);
vector<int> cnt(n);
vector<int> ans(n);
int kind=0;

auto add=[&](int v){
    if(cnt[color[v]]++==0)kind++;
};
auto query=[&](int v){
    ans[v]=kind;
};
auto reset=[&](){
    fill(cnt.begin(),cnt.end(),0);
    kind=0;
};

DsuOnTree solver(tree);
solver.run(add,query,reset);
```

### メソッド

- `void run(Add add,Query query,Reset reset,int root=0)`
  頂点 `root` を根として DSU on Tree を実行します。

  各頂点 `u` について概ね次の順で処理されます。

  1. light な子部分木を `keep=0` で処理してから破棄する
  2. heavy な子部分木を `keep=1` で処理して保持する
  3. 再度 light な子部分木を走査して必要な情報を足し戻す
  4. `add(u)` を呼ぶ
  5. `query(u)` を呼ぶ
  6. `keep==0` なら `reset()` を呼ぶ

### コールバック

- `add(int v)`
  頂点 `v` を現在の集計状態に追加します。
- `query(int v)`
  頂点 `v` を根とする部分木に対する答えを確定させます。
- `reset()`
  現在保持している集計状態を空に戻します。

### 境界・注意

- `Tree::build(root)` が内部で呼ばれるため、事前に `build` していなくても構いません。
- `reset()` は対象部分木の全消去を自前で行う想定です。
- `add` を逆操作付きで書く実装ではなく、不要になったときにまとめて `reset` する設計です。

## 使用例

各頂点の部分木に含まれる色の種類数を求めます。

```cpp
vc<int> color(n),cnt(n),ans(n);
int kind=0;

auto add=[&](int v){
    if(cnt[color[v]]++==0)kind++;
};
auto query=[&](int v){
    ans[v]=kind;
};
auto reset=[&](){
    fill(all(cnt),0);
    kind=0;
};

DsuOnTree solver(tree);
solver.run(add,query,reset);
```
