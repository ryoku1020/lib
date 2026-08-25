---
title: tree
documentation_of: ../../tree/base.hpp
---

# tree

木に対する基本操作と HLD (Heavy-Light Decomposition) をまとめた構造体です。
LCA、距離、パス上の k 番目の頂点、パス分解、部分木区間、直径を扱えます。

木 DP や部分木クエリでは `in/out` を使い、パスクエリでは `query` でパスをいくつかの区間に分けてセグ木などに渡す、という使い方が中心です。

## 使い方

基本の流れは次の通りです。

```cpp
tree tree(n);
for(auto [u,v]:edges)tree.add_edge(u,v);
tree.build();
```

`root` を省略すると `0` を根にします。
`lca`、`dist`、`jump`、`query` などを呼ぶと内部で自動的に `build()` されますが、根を `0` 以外にしたい場合は、最初のクエリを呼ぶ前に `build(root)` してください。

辺が 1-indexed で入力される場合は `input<1>()` が使えます。

```cpp
tree tree(n);
tree.input<1>();
tree.build();
```

重み付き木として使いたい場合は、辺の重み型を指定します。

```cpp
tree<long long> tree(n);
tree.add_edge(a,b,c);
```

## コンストラクタ

### `tree(int n)`

頂点数 `n` の木を作ります。

- 制約: `0<=n`
- 計算量: `O(n)`

## メソッド

### `void tree.add_edge(int a, int b, cost_t cost = 1, int id = -1)`

辺 `a-b` を追加します。
重みなし木では `cost` を省略できます。

- 制約: `0<=a,b<n`
- 計算量: `O(1)` amortized

### `void tree.add_edge(const edge& e)`

`edge` をそのまま追加します。
辺 ID や重みを自分で管理したい場合に使います。

- 計算量: `O(1)` amortized

### `template<int substract> void tree.input()`

辺を `n-1` 本読み込みます。
`substract` を各頂点番号から引いてから追加します。
1-indexed 入力なら `input<1>()`、0-indexed 入力なら `input<0>()` です。

- 計算量: `O(n)`

### `void tree.build(int root = 0) const`

根 `root` を固定して HLD の前計算を行います。

一度 build されると、以後の `build(root)` は何もしません。
根を指定したい場合や、`in/out/par/depth/head/ord` を直接使いたい場合は、先に明示的に呼んでください。

- 制約: `0<=root<n`
- 計算量: `O(n)`

### `int tree.size() const`

頂点数 `n` を返します。

- 計算量: `O(1)`

### `auto tree[u] const`

頂点 `u` から出る辺を列挙できます。

- 制約: `0<=u<n`
- 計算量: `O(次数)`

### `int tree.lca(int a, int b) const`

`a` と `b` の LCA を返します。

- 制約: `0<=a,b<n`
- 計算量: `O(log n)`

### `int tree.dist(int a, int b) const`

`a` と `b` の距離、つまりパス上の辺数を返します。

- 制約: `0<=a,b<n`
- 計算量: `O(log n)`

### `int tree.jumpup(int a, int k) const`

`a` から親方向へ `k` 個上の頂点を返します。
`k==0` なら `a` を返します。
存在しなければ `-1` を返します。

- 制約: `0<=a<n`
- 計算量: `O(log n)`

### `int tree.jump(int s, int t, int k) const`

`s` から `t` への単純パス上で、`s` から距離 `k` の頂点を返します。
`k==0` なら `s`、`k==dist(s,t)` なら `t` です。
範囲外なら `-1` を返します。

- 制約: `0<=s,t<n`
- 計算量: `O(log n)`

### `vc<pair<int,int>> tree.query(int s, int t, bool edge = false) const`

パス `s-t` を HLD 上の区間列に分解して返します。
パス上の頂点値・辺値をセグ木などで処理するときに使います。

`edge=false` なら頂点パス、`edge=true` なら辺パスです。
返る区間は閉区間ベースの `(l,r)` なので、セグ木の半開区間に渡すときは `[min(l,r),max(l,r)+1)` に変換します。

- 制約: `0<=s,t<n`
- 計算量: `O(log n)`

### `pair<int,int> tree.get_diameter() const`

木の直径の両端を返します。
重み付き木でも、ここでの直径は辺数で見た直径です。

- 制約: `n>0`
- 計算量: `O(n)`

## 主要メンバ

- `in[v]`, `out[v]`
  Euler Tour / HLD 順です。部分木 `v` は `[in[v],out[v])` で表せます。
- `depth[v]`
  根からの深さです。
- `par[v]`
  根付き木での親です。根の親は `-1` です。
- `head[v]`
  `v` が属する heavy path の先頭です。
- `size_[v]`
  根付き木で見た `v` の部分木サイズです。
- `ord`
  `ord[in[v]] == v` となる頂点列です。

## インデックスと境界

`build(root)` 後、各頂点には HLD / Euler Tour 順の番号 `in[v]` が付きます。
この番号を使うと、頂点値を配列やセグ木に載せられます。

- 頂点 `v` の部分木は半開区間 `[in[v],out[v])`
- `ord[in[v]] == v`
- `depth[v]` は `root` からの深さ
- `par[v]` は根付き木での親で、根の親は `-1`

`query(s,t,edge)` が返す区間だけは、半開区間ではなく閉区間のペアです。
各ペア `(l,r)` は `in` 配列上の区間で、返る順番はパス `s -> t` の順です。

- `l<=r` なら `in` の小さい方から大きい方へ進む
- `l>r` なら `in` の大きい方から小さい方へ進む
- セグ木で区間取得するだけなら `[min(l,r),max(l,r)+1)` を使う
- 非可換な演算では、`l>r` の区間を逆向きに扱う必要がある

`edge=false` のときは頂点パスです。
`s` と `t` の両端、LCA の頂点を含みます。

`edge=true` のときは辺パスです。
各辺を「深い側の頂点」に対応させ、LCA の頂点は除きます。
そのため `s==t` のときは空の区間列になります。

## 境界・注意

- 木であることを仮定しています。連結性や閉路の有無は実行時には検査しません。
- 辺を追加した後、最初のクエリや `build` によって HLD 情報が固定されます。build 後に辺を追加して使い直すことは想定していません。
- 根を `0` 以外にしたい場合は、自動 build が走る前に `build(root)` を呼んでください。
- `in/out` の部分木区間は半開区間 `[l,r)`、`query` の返すパス区間は閉区間 `(l,r)` です。
- `get_diameter` は `build` とは独立に DFS します。

## 使用例 1: LCA と距離

```cpp
#include "tree/base.hpp"

int N,Q;
cin>>N>>Q;
tree tree(N);
rep(i,N-1){
    int u,v;
    cin>>u>>v;
    tree.add_edge(u,v);
}
tree.build();

rep(q,Q){
    int u,v;
    cin>>u>>v;
    int w=tree.lca(u,v);
    int d=tree.dist(u,v);
    cout<<w<<" "<<d<<"\n";
}
```

## 使用例 2: 部分木和

頂点 `v` の部分木は `[in[v],out[v])` に対応します。
頂点値 `A[v]` を `in[v]` 番目に並べてセグ木に載せます。

```cpp
tree tree(N);
rep(i,N-1){
    int u,v;
    cin>>u>>v;
    tree.add_edge(u,v);
}
tree.build(root);

segtree<info> seg(N,[&](int i){
    return A[tree.ord[i]];
});

auto ans=seg.prod(tree.in[v],tree.out[v]);
```

## 使用例 3: 頂点パスクエリ

`query(u,v)` は、パス `u -> v` を `in` 配列上の閉区間列に分解します。
和や max のように向きを気にしない演算なら、各区間を半開区間へ直して処理します。

```cpp
long long ans=0;
for(auto [l,r]:tree.query(u,v)){
    ans+=seg.prod(min(l,r),max(l,r)+1);
}
```

非可換な演算では、`l>r` の区間を逆向きに読む必要があります。
その場合は、順方向用と逆方向用の値を両方持つセグ木にしておくと扱いやすいです。

```cpp
info ans=info::e();
for(auto [l,r]:tree.query(u,v)){
    if(l<=r){
        ans=info::op(ans,seg.prod(l,r+1).forward);
    }else{
        ans=info::op(ans,seg.prod(r,l+1).backward);
    }
}
```

## 使用例 4: 辺パスクエリ

辺の値を深い側の頂点に置くと、`query(u,v,true)` で辺パスを処理できます。
LCA の頂点は除かれるので、`u==v` のときは空です。

```cpp
rep(v,N){
    for(auto e:tree[v]){
        if(tree.par[e.to]==v){
            seg.set(tree.in[e.to],edge_value[e.id]);
        }
    }
}

long long ans=0;
for(auto [l,r]:tree.query(u,v,true)){
    ans+=seg.prod(min(l,r),max(l,r)+1);
}
```
