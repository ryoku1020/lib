---
title: Wavelet matrix
documentation_of: ../../ds/sequence/wavelet-matrix.hpp
---

# Wavelet matrix

整数列に対する区間クエリ（k番目最小値・値の個数・値の個数）を高速に処理するデータ構造です。

## 型

```cpp
wavelet_matrix<T, depth>
```

- `T` — 要素の型（整数型: `int`, `long long` など）
- `depth` — 使用するビット深さ。扱える値の範囲は `[0, 2^depth)` です。

## コンストラクタ

### `wavelet_matrix<T, depth>(int n = 0)`

要素数 `n` で初期化します。

## メソッド

### `void wm.set(int i, T x)`

インデックス `i` に値 `x` をセットします。`build()` の前に呼ぶ必要があります。

- 制約: `0<=i<n`, `0<=x<2^depth`

### `void wm.build()`

内部データを構築します。すべての `set()` を終えてから必ず呼んでください。

- 計算量: `O(n * depth)`

### `T wm.kth_smallest(int l, int r, T k)`

`[l, r)` 内の要素を昇順に並べたとき `k` 番目（0-indexed）の値を返します。

- 制約: `0<=l<=r<=n`, `0<=k<r-l`（空区間・範囲外は `assert` で停止）
- 計算量: `O(depth)`

### `int wm.count_lower(int l, int r, T k)`

`[l, r)` 内の要素のうち、値が **`k` 以下** のものの個数を返します。

- 制約: `0<=l<=r<=n`
- 計算量: `O(depth)`

### `int wm.count(int l, int r, T x)`

`[l, r)` 内の要素のうち、値がちょうど `x` であるものの個数を返します。

内部では `count_lower(l,r,x) - count_lower(l,r,x-1)` で計算されます。

- 制約: `0<=l<=r<=n`, **`x>=1`**（`x==0` で `T` が符号なし整数のとき `x-1` がアンダーフローする）
- 計算量: `O(depth)`

## bit_vector

`wavelet_matrix` が内部で使う簡潔ビットベクトルです。

```cpp
bit_vector(const vc<int>& v) // 0/1 配列から構築 O(N)
int rank1(int r)              // [0,r) の 1 の個数 O(1)
int rank1(int l, int r)       // [l,r) の 1 の個数 O(1)
int rank0(int r)              // [0,r) の 0 の個数 O(1)
int rank0(int l, int r)       // [l,r) の 0 の個数 O(1)
```

## 境界・注意

- `count(l,r,0)` は `T` が符号なし整数のとき `0-1` がアンダーフローするため**使用不可**です。
  0 の個数が必要な場合は `(r-l) - count_lower(l, r, 0) + count_lower(l, r, 0)` ではなく、
  `count_lower(l,r,0)` の値をそのまま使ってください（`count_lower(l,r,0)` = 0 以下の個数 = 0 の個数）。
- 扱う値は `[0, 2^depth)` の範囲でなければなりません。

## 使用例

```cpp
#include "ds/sequence/wavelet-matrix.hpp"

wavelet_matrix<int, 20> wm(n); // [0, 2^20) の範囲の整数
for(int i=0;i<n;i++) wm.set(i, a[i]);
wm.build();

// [l,r) の中央値（0-indexed の (r-l)/2 番目）
auto med = wm.kth_smallest(l, r, (r-l)/2);

// [l,r) に含まれる 5 以下の要素数
auto cnt_le5 = wm.count_lower(l, r, 5);

// [l,r) に含まれる値 7 の個数（7>=1 なので OK）
auto cnt7 = wm.count(l, r, 7);
```
