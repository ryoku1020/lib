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

根から `p/q` へ向かうパス上で、根からの深さが `d` の祖先ノードを返します。
`d = 0` は根、`d` が `p/q` の深さを超える場合は `nullopt` です。

### `pair<pair<T,T>,pair<T,T>> stern_brocot_tree<T>::range(T p, T q)`

分数 `p/q` に対応する Stern-Brocot 木ノードの「左境界分数」と「右境界分数」を返します。
`{left_frac, right_frac}` の形で、それぞれ `{p_i, q_i}` です。

## 計算量

`k` を Euclid の互除法で得る商の個数、`d` を通常の `L` / `R` 1 ステップ単位での木の深さとします。

- `encode_path`: 時間 `O(k) = O(log(min(a,b))+1)`、返り値 `O(k)` 個
- `decode_path(c)`: 時間 `O(|c|)`、追加メモリ `O(1)`
- `lca`: 時間・一時メモリ `O(k1+k2)`
- `ancestor`, `range`: 時間・一時メモリ `O(k)`

パスは同じ向きの連続移動を `{方向, 回数}` に圧縮しているため、実行時間は `d` ではなく商の個数に比例します。ただし回数の総和である木の深さ `d` 自体は大きくなり得ます。

## 境界・注意

- 分数の分子・分母は正でなければなりません（`assert` あり）。既約でない入力も Euclid の互除法により同じ有理数のノードへ正規化されます。
- `ancestor(1,1,0)` は本来なら根ですが、圧縮パスが空のため現在の実装は `nullopt` を返します。それ以外の正の分数では `d = 0` で根を返します。
- `decode_path` の各方向は `'L'` または `'R'`、移動回数は非負でなければなりません（`assert` あり）。標準形にしたい場合は `encode_path` の返り値を使ってください。
- `st_frac` は境界として `0/1` と `1/0` も保持します。`range(1,1)` はこの 2 つを返します。
- `p*w`, `q*w` とその加算が `T` の範囲を超えない必要があります。オーバーフローは検出されません。

## 使用例

```cpp
#include "math/number_theory/stern-brocot-tree.hpp"

using SBT = stern_brocot_tree<long long>;

// p/q へのパスを符号化
auto path = SBT::encode_path(3, 5);
// path == {{'L',1},{'R',1},{'L',1}}

// パスをデコード
auto node = SBT::decode_path(path);
auto [num, den] = node.to_frac(); // = {3, 5}

// 2/3 と 5/7 の LCA
auto lca_node = SBT::lca(2, 3, 5, 7);
auto [ln, ld] = lca_node.to_frac();

// 根から 2 ステップ進んだ、3/5 の祖先
auto anc = SBT::ancestor(3, 5, 2);
if(anc) {
    auto [an, ad] = anc->to_frac();
}

// 3/5 のノードが表す範囲
auto [left_f, right_f] = SBT::range(3, 5);
// left_f = {p_l, q_l}, right_f = {p_r, q_r}
```
