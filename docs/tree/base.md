---
title: Tree
documentation_of: ../../tree/base.hpp
---

# Tree

木に対する基本操作と HLD をまとめた構造体です。
LCA、距離、パス分解、部分木区間などを扱えます。

## コンストラクタ

### `Tree(int n)`

頂点数 `n` の木を作ります。

- 制約: `0<=n`
- 計算量: `O(n)`

## メソッド

### `void tree.add_edge(int a, int b)`

辺 `a-b` を追加します。

- 制約: `0<=a,b<n`
- 計算量: `O(1)` amortized

### `template<int subtract> void tree.input()`

辺を `n-1` 本読み込みます。
1-indexed 入力なら `input<1>()` のように使います。

### `void tree.build(int root = 0) const`

根 `root` を固定して HLD の前計算を行います。
`lca` や `dist` などを初めて呼んだときにも内部で自動実行されます。

- 計算量: `O(n)`

### `int tree.lca(int a, int b) const`

`a` と `b` の LCA を返します。

- 計算量: `O(log n)`

### `int tree.dist(int a, int b) const`

`a` と `b` の距離を返します。

- 計算量: `O(log n)`

### `int tree.jumpup(int a, int k) const`

`a` から親方向へ `k` 個上の頂点を返します。
存在しなければ `-1` を返します。

- 計算量: `O(log n)`

### `int tree.jump(int s, int t, int k) const`

`s` から `t` への単純パス上で、`s` から距離 `k` の頂点を返します。
存在しなければ `-1` を返します。

- 計算量: `O(log n)`

### `vc<pair<int,int>> tree.Query(int s, int t) const`

パス `s-t` を HLD 上の区間列に分解して返します。
各要素は `in` 配列上の閉区間で、向き付きです。

- `first<=second`
  左から右に進む区間
- `first>second`
  右から左に進む区間

パスをセグ木で処理するときに使います。

- 計算量: `O(log n)`

### `pair<int,int> tree.get_diameter() const`

木の直径の両端を返します。

- 計算量: `O(n)`

## 主要メンバ

- `in[v]`, `out[v]`
  Euler Tour / HLD 順です。部分木 `v` は `[in[v],out[v])` で表せます。
- `depth[v]`
  根からの深さ
- `par[v]`
  親
- `head[v]`
  `v` が属する heavy path の先頭
- `ord`
  `in` の逆写像に近い順序配列

## 使用例 1: 部分木和

```cpp
Tree tree(n);
for(auto [u,v]:edges)tree.add_edge(u,v);
tree.build();

// 頂点 v の部分木は [in[v],out[v]) に対応
auto ans=seg.prod(tree.in[v],tree.out[v]);
```

## 使用例 2: パスクエリ

```cpp
auto path=tree.Query(u,v);
for(auto [l,r]:path){
    if(l<=r){
        // 区間 [l,r] を順方向に使う
    }else{
        // 区間 [r,l] を逆方向に使う
    }
}
```

## 注意

- 木であることを仮定しています。
- `Query` が返すのは半開区間ではなく閉区間ベースのペアです。
- `build(root)` 後は、その `root` に対する親子関係と深さになります。
