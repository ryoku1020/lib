---
title: assign_segtree
documentation_of: ../../ds/segment_tree/assign-segtree.hpp
---

# assign_segtree

区間代入と区間積取得を行うセグメント木です。
`lazy_segtree` で「代入作用」を実現するより効率的に動作します。

## 要件

```cpp
struct info{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

通常の `segtree` と同じ `info` を使えます。

## コンストラクタ

### `assign_segtree<info>(int n, value_type leaf = info::e())`

長さ `n` で初期化します。
各要素は `leaf` で初期化されます。

- 計算量: `O(n)`

## メソッド

### `void seg.assign(int l, int r, value_type x)`

区間 `[l,r)` の全要素を `x` に代入します。

- 制約: `0<=l<=r<=n`
- 計算量: ならし `O(log n)`

### `value_type seg.prod(int l, int r)`

`op(a[l],...,a[r-1])` を返します。

- 制約: `0<=l<=r<=n`
- 計算量: `O(log n)`

### `void seg.set(int i, value_type x)`

`a[i]=x` とします（1 点代入）。

- 制約: `0<=i<n`
- 計算量: `O(log n)`

### `void seg.reset()`

内部にたまった代入テーブルを全解決してリセットします。
代入回数が多くなったときに手動で呼ぶことでメモリを整理できます。

## 境界・注意

- 区間代入専用です。「加算」や「affine 変換」のような一般遅延作用には `lazy_segtree` を使ってください。
- 内部で代入テーブルが蓄積されるため、大量の代入後は `reset()` を呼ぶとメモリ効率が改善することがあります（コメントアウト中の自動化コードあり）。

## 使用例: 区間代入・区間最大値

```cpp
#include "ds/segment_tree/assign-segtree.hpp"

struct info{
    using value_type = long long;
    static value_type op(value_type a,value_type b){ return max(a,b); }
    static value_type e(){ return -(ll)4e18; }
};

assign_segtree<info> seg(n);

seg.assign(l, r, x);        // [l,r) を全部 x に
auto ans = seg.prod(l, r);  // [l,r) の最大値
```

## 使用例: 区間代入・区間和

```cpp
struct info{
    using value_type = pair<long long,int>; // {sum, len}
    static value_type op(value_type a,value_type b){
        return {a.first+b.first, a.second+b.second};
    }
    static value_type e(){ return {0,0}; }
};

assign_segtree<info> seg(N,{0,1});

// assign(l,r,{x,1}) で [l,r) を全部 x にしたとき
// sum はセグ木が自動で len * x を計算してくれる
seg.assign(l, r, {x, 1});
auto [sum, len] = seg.prod(0, n);
```
