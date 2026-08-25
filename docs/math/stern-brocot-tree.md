---
title: stern_brocot_tree
documentation_of: ../../math/number_theory/stern-brocot-tree.hpp
---

# stern_brocot_tree

Stern-Brocot 木に関する操作を提供します。
Stern-Brocot 木は、正の既約分数をすべて一度だけ含む二分探索木です。

## 型

```cpp
stern_brocot_tree<T>
```

`T` は整数型（`long long` など）。

## 内部型

### `st_frac`

Stern-Brocot 木のノードを表します。
各ノードは隣接する分数 `(p/q, r/s)` の対として表現され、そのノードが表す分数は `(p+r)/(q+s)` です。

```cpp
struct st_frac{
    T p,q,r,s;
    pair<T,T> to_frac(); // (p+r, q+s) を返す
};
```

## メソッド（すべて static）

### `vc<pair<char,T>> stern_brocot_tree<T>::encode_path(T a, T b)`

分数 `a/b` への Stern-Brocot 木上のパスをエンコードします。
返り値は `{'L' or 'R', 何ステップ}` のリストです。

### `st_frac stern_brocot_tree<T>::decode_path(vc<pair<char,T>> c)`

エンコードされたパスをデコードしてノードを返します。

### `st_frac stern_brocot_tree<T>::lca(T p1, T q1, T p2, T q2)`

分数 `p1/q1` と `p2/q2` の Stern-Brocot 木上での LCA ノードを返します。

### `optional<st_frac> stern_brocot_tree<T>::ancestor(T p, T q, T d)`

分数 `p/q` の `d` ステップ上の祖先ノードを返します。
到達できなければ `nullopt`。

### `pair<pair<T,T>,pair<T,T>> stern_brocot_tree<T>::range(T p, T q)`

分数 `p/q` に対応する Stern-Brocot 木ノードの「左境界分数」と「右境界分数」を返します。
`{left_frac, right_frac}` の形で、それぞれ `{p_i, q_i}` です。

## 境界・注意

- 入力はすべて正の既約分数（`gcd(a,b)=1`, `a,b > 0`）を前提としています。
- パスの長さは `O(a+b)` になり得ます（ユークリッド互除法の步数に比例）。

## 使用例

```cpp
#include "math/number_theory/stern-brocot-tree.hpp"

using SBT = stern_brocot_tree<long long>;

// p/q へのパスを符号化
auto path = SBT::encode_path(3, 5);
// → [('L',1),('R',2)] のような形式

// パスをデコード
auto node = SBT::decode_path(path);
auto [num, den] = node.to_frac(); // = {3, 5}

// 2/3 と 5/7 の LCA
auto lca_node = SBT::lca(2, 3, 5, 7);
auto [ln, ld] = lca_node.to_frac();

// 3/5 の 2 ステップ上の祖先
auto anc = SBT::ancestor(3, 5, 2);
if(anc) {
    auto [an, ad] = anc->to_frac();
}

// 3/5 のノードが表す範囲
auto [left_f, right_f] = SBT::range(3, 5);
// left_f = {p_l, q_l}, right_f = {p_r, q_r}
```
