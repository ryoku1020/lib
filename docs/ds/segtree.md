---
title: Segtree
documentation_of: ../../ds/segtree.hpp
---

# Segtree

モノイドを載せる通常のセグメント木です。
1 点更新、区間積取得、`max_right` / `min_left` による二分探索を行えます。

## 要件

```cpp
struct Info{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

- `op`
  結合法則を満たす二項演算
- `e`
  単位元
## コンストラクタ

### `Segtree(int n = 0, value_type leaf = Info::e())`

長さ `n` の列を作ります。
各要素は `leaf` で初期化されます。

- 制約: `0<=n`
- 計算量: `O(n)`

### `template<class F> Segtree(int n, F f)`

`a[i]=f(i)` で初期化します。

- 計算量: `O(n)`

## メソッド

### `void seg.set(int p, value_type x)`

`a[p]=x` とします。

- 制約: `0<=p<n`
- 計算量: `O(log n)`

### `void seg.apply(int p, value_type x)`

`a[p]=op(a[p],x)` とします。

- 制約: `0<=p<n`
- 計算量: `O(log n)`

### `value_type seg.prod(int l, int r)`

`op(a[l],...,a[r-1])` を返します。
`l==r` のときは `e()` を返します。

- 制約: `0<=l<=r<=n`
- 計算量: `O(log n)`

### `value_type seg.all_prod()`

`op(a[0],...,a[n-1])` を返します。

- 計算量: `O(1)`

### `int seg.max_right(int l, F f)`

以下を満たす `r` を 1 つ返します。

- `r=l` または `f(op(a[l],...,a[r-1]))=true`
- `r=n` または `f(op(a[l],...,a[r]))=false`

`f` が単調なら、「`f(prod(l,r))` が真である最大の `r`」とみなせます。

- 制約: `f(e())=true`, `0<=l<=n`
- 計算量: `O(log n)`

### `int seg.min_left(int r, F f)`

以下を満たす `l` を 1 つ返します。

- `l=r` または `f(op(a[l],...,a[r-1]))=true`
- `l=0` または `f(op(a[l-1],...,a[r-1]))=false`

`f` が単調なら、「`f(prod(l,r))` が真である最小の `l`」とみなせます。

- 制約: `f(e())=true`, `0<=r<=n`
- 計算量: `O(log n)`

## 境界・注意

- 区間は 0-indexed の半開区間 `[l,r)` です。
- 初期値を `e()` 以外にしたいときは `Segtree(n, leaf)` で渡します。

## 使用例 1: Range Max Query

```cpp
#include "ds/segtree.hpp"

struct Info{
    using value_type=long long;
    static value_type op(value_type a,value_type b){
        return max(a,b);
    }
    static value_type e(){
        return -(long long)4e18;
    }
};

Segtree<Info> seg(N);
seg.set(i,x);
auto ans=seg.prod(l,r);
```

## 使用例 2: prefix 和が `X` 以下の最大位置

```cpp
struct Info{
    using value_type=long long;
    static value_type op(value_type a,value_type b){ return a+b; }
    static value_type e(){ return 0; }
};

Segtree<Info> seg(N,f);
long long X=100;
int r=seg.max_right(0,[&](long long s){ return s<=X; });
```
