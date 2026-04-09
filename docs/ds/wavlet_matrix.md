---
title: Wavelet Matrix
documentation_of: ../../ds/wavlet_matrix.hpp
---

# Wavelet Matrix

整数列に対する区間クエリ（区間内の特定の要素の個数、区間内の $k$ 番目に小さい値など）を高速に処理できるデータ構造です。内部で簡潔ビットベクトル (`bit_vector`) を用いています。

## bit_vector

長さを $N$ としたとき、$0, 1$ の列に対する `rank`（指定区間に含まれる $1$ や $0$ の個数）クエリを $O(1)$ で処理する構造体です。

### コンストラクタ
- `bit_vector(const vc<int>& v)`: $0, 1$ の配列 `v` から構築します。$O(N)$

### メソッド
- `int rank1(int r)`: 半開区間 $[0, r)$ に含まれる $1$ の個数を返します。
- `int rank1(int l, int r)`: 半開区間 $[l, r)$ に含まれる $1$ の個数を返します。
- `int rank0(int r)`: 半開区間 $[0, r)$ に含まれる $0$ の個数を返します。
- `int rank0(int l, int r)`: 半開区間 $[l, r)$ に含まれる $0$ の個数を返します。

## wavlet_matrix

### テンプレート引数
- `class T`: 扱う値の型（整数型）
- `int depth`: 値の最大ビット幅

### メソッド

- `wavlet_matrix(int n = 0)`
  要素数 $n$ で初期化します。

- `void set(int i, T x)`
  インデックス $i$ に値 $x$ をセットします。構築前に呼び出す必要があります。

- `void build()`
  内部の `bit_vector` などのデータ構造を構築します。`set` で全ての値を設定し終えた後に必ず呼び出してください。
  計算量: $O(N \cdot \text{depth})$

- `T kth_smallest(int l, int r, T k)`
  半開区間 $[l, r)$ に含まれる要素の中で $k$ 番目 ($0$-indexed) に小さい値を返します。
  計算量: $O(\text{depth})$

- `int count_lower(int l, int r, T k)`
  半開区間 $[l, r)$ に含まれる要素の中で、値が $k$ 以下のものの個数を返します。
  計算量: $O(\text{depth})$

- `int count(int l, int r, T x)`
  半開区間 $[l, r)$ に含まれる要素の中で、値がちょうど $x$ であるものの個数を返します。
  計算量: $O(\text{depth})$
