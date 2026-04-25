---
title: DualSegmentTree
documentation_of: ../../ds/dual.hpp
---

# DualSegmentTree

区間更新・一点取得の dual segment tree です。

## 要件

```cpp
struct X{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

ここで `op` は作用の合成として使われます。

## コンストラクタ

### `DualSegmentTree(int N)`

長さ `N` を `e()` で初期化します。

### `DualSegmentTree(int N, const vc<value_type>& v)`

初期列 `v` で初期化します。

## メソッド

### `void seg.build(const vc<value_type>& v)`

葉を `v` で初期化します。

### `void seg.set(int p, value_type x, bool is_first = false)`

位置 `p` の値を `x` に設定します。
`is_first=true` は build 前提の軽量設定です。

### `void seg.apply(int l, int r, value_type x)`

区間 `[l,r)` に作用 `x` を適用します。

- 制約: `0<=l<=r<=N`
- 計算量: `O(log N)`

### `value_type seg.get(int p)`

位置 `p` の値を返します。

- 制約: `0<=p<N`
- 計算量: `O(log N)`

## 使用例

```cpp
#include "ds/dual.hpp"

struct X{
    using value_type=long long;
    static value_type op(value_type a,value_type b){ return a+b; }
    static value_type e(){ return 0; }
};

DualSegmentTree<X> seg(n);
seg.apply(l,r,x);
auto v=seg.get(p);
```

## 注意

- 取れるのは一点値だけです。区間積取得はできません。
