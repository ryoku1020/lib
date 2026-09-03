---
title: wm_base (Wavelet Matrix)
documentation_of: ../../ds/sequence/wavelet-matrix.hpp
---

# wm_base (Wavelet Matrix)

非負整数列に対する k 番目最小値、値域内の個数、重み和を処理する Wavelet Matrix です。

## 型

```cpp
wm_base<T,D>
```

- `T` — 要素の整数型
- `D` — 使用する下位ビット数。要素の値域は `[0,2^D)`

## 構築

### `void wm.build(vc<T> a)`

配列 `a` を使って Wavelet Matrix を構築します。長さはこの呼び出しで決まります。

- 制約: すべての `a[i]` が `0<=a[i]<2^D`
- 計算量: `O(nD)`

### `void wm.buildlowersum<L>(const vc<L>& W)`

各位置の重み `W[i]` を使い、値による絞り込みと重み和を組み合わせる前計算を行います。先に `build()` を呼んでください。

- 制約: `W.size()==n`
- 計算量: `O(nD)`

## クエリ

### `T wm.kth_smallest(int l,int r,int k) const`

`a[l,r)` を昇順に並べたときの `k` 番目を返します。`k` は 0-indexed です。

- 制約: `0<=l<=r<=n`, `0<=k<r-l`
- 計算量: `O(D)`

### `long long wm.count_less(int l,int r,T u) const`

`a[l,r)` に含まれる `u` 未満の要素数を返します。

- 制約: `0<=l<=r<=n`, `0<=u<2^D`
- 計算量: `O(D)`

### `long long wm.count(int l,int r,T d,T u) const`

`a[l,r)` に含まれる値域 `[d,u)` の要素数を返します。

- 制約: `0<=l<=r<=n`, `0<=d<=u<2^D`
- 計算量: `O(D)`

### `L wm.lower_sum<L>(int l,int r,T u) const`
### `L wm.lower_sum<L>(int l,int r,T d,T u) const`

それぞれ `a[l,r)` のうち値が `[0,u)`、`[d,u)` に入る位置の重み `W[i]` の総和を返します。先に同じ `L` で `buildlowersum<L>(W)` を呼んでください。

- 制約: `0<=l<=r<=n`, `0<=d<=u<2^D`
- 計算量: `O(D)`

## 計算量

構築と重み和の前計算はそれぞれ `O(nD)`、各クエリは `O(D)` です。Wavelet Matrix 本体の使用メモリは `O(nD/64+D)`、重み和を構築した場合の prefix 配列は `O(nD)` です。

## 境界・注意

- 区間と値域はどちらも 0-indexed の半開区間です。
- 各クエリは引数を `assert` していません。空区間に `kth_smallest` を呼ぶ、または範囲外の `k` を渡すと正しい結果になりません。
- `count_less` / `count` / `lower_sum` は `D` より上位のビットを見ません。上端 `u==2^D` は全要素を数える番兵として使えません。全区間の個数は `r-l` を使い、最大値 `2^D-1` の個数は `(r-l)-count_less(l,r,2^D-1)` で求められます。
- 重み和の prefix 配列は型 `L` ごとの static 領域です。同じ `T,D,L` の別インスタンスで `buildlowersum` を呼ぶと上書きされるため、その型の重み和クエリを同時に使うインスタンスは 1 つにしてください。

## 使用例

```cpp
#include "ds/sequence/wavelet-matrix.hpp"

wm_base<int,20> wm;
wm.build(a);

// [l,r) の中央値
int med=wm.kth_smallest(l,r,(r-l)/2);

// [l,r) にある [3,8) の値の個数
long long cnt=wm.count(l,r,3,8);

// 値が 10 未満である位置の重みの総和
wm.buildlowersum<long long>(weight);
long long sum=wm.lower_sum<long long>(l,r,10);
```
