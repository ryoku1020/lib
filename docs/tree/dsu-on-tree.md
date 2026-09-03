---
title: DSU on tree
documentation_of: ../../tree/dsu-on-tree.hpp
---

# DSU on tree

いわゆる Sack / DSU on tree を行うための薄いラッパーです。
`tree` の heavy-light 情報を利用して、light な部分木を先に捨て、heavy な部分木だけを保持する順で DFS を進めます。

## `dsu_on_tree<tree>`

> **現行実装の互換性**: `dsu_on_tree` 自体は `build`, `heavy_edge`, `light_edges` を持つ木型に対するテンプレートです。しかし同じリポジトリの `tree/base.hpp` にある `tree::heavy_edge` と `tree::light_edges` は、存在しない `Graph::span` を参照するため、以下の `tree` を使った例は現状のままではコンパイルできません。

### 使い方

```cpp
#include "tree/dsu-on-tree.hpp"

tree tree(n);
// 辺を追加

dsu_on_tree solver(tree);

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

dsu_on_tree solver(tree);
solver.run(add,query,reset);
```

### メソッド

- `void run(add_func add,query query,reset_func reset,int root=0)`
  頂点 `root` を根として DSU on tree を実行します。

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

## 計算量

互換性のある木型を渡せる場合、頂点数を $N$ とすると、`add` は合計 `O(N log N)` 回、`query` はちょうど `N` 回、`reset` は高々 `N` 回呼ばれます。したがって各コールバックが `O(1)` なら全体は `O(N log N)` 時間です。

一般には、各コールバックの実行時間をそれぞれ $A,Q,R$ として `O(N log N A+NQ+NR)` が上界です。内部の追加領域は再帰スタックを含めて `O(N)` です。`reset` で毎回長さ `N` の配列を `fill` すると全体が `O(N^2)` になり得るため、必要なら実際に触れた要素だけを消してください。

現行の `tree/base.hpp` と組み合わせた利用可能な実装としてはコンパイルが成立しないため、その組み合わせの実行時計算量は定義されません。

### 境界・注意

- `0<=root<tree.size()` が必要です。空の木には使えません。
- 渡す木型は `size()`, `build(root)`, `heavy_edge(u)`, `light_edges(u)` を持ち、後二者の要素が `.to` を持つ必要があります。
- 現行の `tree/base.hpp` を直接渡すと、上記 `Graph::span` の型エラーになります。利用するには木型側の `heavy_edge` / `light_edges` を `std::span` などで返すよう修正するか、同等 API のアダプタを用意してください。
- `tree::build(root)` が内部で呼ばれるため、事前に `build` していなくても構いません。ただし木がすでに別の根で build 済みの場合、`tree::build(root)` は根を変更しません。未構築の木か、同じ `root` で構築済みの木を渡してください。
- `reset()` は対象部分木の全消去を自前で行う想定です。
- `add` を逆操作付きで書く実装ではなく、不要になったときにまとめて `reset` する設計です。
- `query(v)` が呼ばれる時点では、現在の集計状態に `v` の部分木の頂点がちょうど入っています。最後に根の処理でも `reset()` が呼ばれるため、正常終了後の集計状態は空です。
- 木であることを仮定し、内部 DFS は再帰で行います。

## 使用例

各頂点の部分木に含まれる色の種類数を求めます。

```cpp
vc<int> color(n),cnt(n),ans(n),touched;
int kind=0;

auto add=[&](int v){
    if(cnt[color[v]]++==0){
        kind++;
        touched.pb(color[v]);
    }
};
auto query=[&](int v){
    ans[v]=kind;
};
auto reset=[&](){
    for(int c:touched)cnt[c]=0;
    touched.clear();
    kind=0;
};

dsu_on_tree solver(tree);
solver.run(add,query,reset);
```
