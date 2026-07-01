---
title: LazySegtree
documentation_of: ../../ds/lazy-segtree.hpp
---

# LazySegtree

区間に対する作用と、区間積の取得を両方 `O(log N)` で行う遅延セグメント木です。
ACL の `lazy_segtree` と同じく、「値のモノイド」と「その上に作用する写像」を分けて与える設計ですが、この実装ではオラクル名が `op / e / mapping / composition / id` ではなく `Info` / `Tag` 構造体で与える形になっています。

## 要件

`Info` と `Tag` には次を定義します。

### `Info`

```cpp
struct Info{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

- `value_type`
  セグ木の各ノードに乗る型です。
- `op`
  区間をマージする二項演算です。結合法則を満たす必要があります。
- `e`
  `op` の単位元です。
### `Tag`

```cpp
struct Tag{
    using lazy_type=...;
    static Info::value_type Apply(Info::value_type x,lazy_type f);
    static lazy_type Merge(lazy_type old_tag,lazy_type new_tag);
    static lazy_type id();
};
```

- `lazy_type`
  遅延作用素の型です。
- `Apply`
  値 `x` に作用素 `f` を適用した結果を返します。
- `Merge`
  すでに積まれている遅延 `old_tag` に、新しい遅延 `new_tag` を後から積んだ結果を返します。
- `id`
  恒等作用です。

### 作用の考え方

ACL と同様に、`Tag::Apply` は「1 要素」ではなく「そのノードが表す区間全体の集約値」に作用させます。
そのため、区間和に affine 変換をかけたい場合は、ノードに `sum` だけでなく `len` も持たせる必要があります。

## コンストラクタ

### `LazySegtree(int N, value_type leaf = Info::e())`

長さ `N` の列を作ります。
各要素は `leaf` で初期化されます。

- 制約: `0<=N`
- 計算量: `O(N)`

### `LazySegtree(int N, vc<value_type> A)`

長さ `N` の列を `A` で初期化します。

- 制約: `0<=N`, `A.size()<=N` を想定
- 計算量: `O(N)`

### `template<class F> LazySegtree(int N, F f)`

`f(i)` を初期値として長さ `N` の列を作ります。

- 計算量: `O(N)`

## メソッド

### `void seg.set(int p, value_type x)`

`a[p]=x` とします。
途中に未反映の遅延があっても、対象点まで push してから正しく上書きします。

- 制約: `0<=p<N`
- 計算量: `O(log N)`

### `value_type seg.prod(int l, int r)`

`op(a[l],a[l+1],...,a[r-1])` を返します。
`l==r` のときは `e()` を返します。

- 制約: `0<=l<=r<=N`
- 計算量: `O(log N)`

### `void seg.apply(int l, int r, lazy_type f)`

`l<=i<r` について `a[i]` に作用素 `f` を適用します。

- 制約: `0<=l<=r<=N`
- 計算量: `O(log N)`

### `value_type seg.all_prod()`

`op(a[0],a[1],...,a[N-1])` を返します。

- 計算量: `O(1)`

### `int seg.max_right(int l, F f)`

`f(op(a[l],...,a[r-1]))` が true になる最大の `r` を返します。
`Segtree` と同様に、`f(e())` が true で、条件が単調であることを想定しています。

- 制約: `0<=l<=N`
- 計算量: `O(log N)`

### `int seg.min_left(int r, F f)`

`f(op(a[l],...,a[r-1]))` が true になる最小の `l` を返します。
`Segtree` と同様に、`f(e())` が true で、条件が単調であることを想定しています。

- 制約: `0<=r<=N`
- 計算量: `O(log N)`

## この実装にない ACL API

ACL の `lazy_segtree` にある次の API は、この実装にはありません。

- `get`
- 1 点 `apply`

必要なら `prod(p,p+1)` で 1 点取得はできますが、計算量は `O(log N)` です。

## 境界・注意

- 区間はすべて 0-indexed の半開区間 `[l,r)` です。
- `Tag::Merge(old_tag,new_tag)` の順序を取り違えると壊れやすいです。「もともと積まれていたものに、後から新しい作用を乗せる」と読んで書くと安全です。
- 初期値を `e()` 以外にしたいときは `LazySegtree(N, leaf)`、各要素を直接与えたいときは `LazySegtree(N, A)` か `LazySegtree(N, f)` を使います。

## 使用例 1: 区間加算・区間最小値

```cpp
#include "ds/lazy-segtree.hpp"

struct Info{
    using value_type=long long;
    static value_type op(value_type a,value_type b){
        return min(a,b);
    }
    static value_type e(){
        return (long long)4e18;
    }
};

struct Tag{
    using lazy_type=long long;
    static value_type Apply(value_type x,lazy_type f){
        return x+f;
    }
    static lazy_type Merge(lazy_type old_tag,lazy_type new_tag){
        return old_tag+new_tag;
    }
    static lazy_type id(){
        return 0;
    }
};

LazySegtree<Info,Tag> seg(N,A);
seg.apply(l,r,x);
auto ans=seg.prod(l,r);
```

## 使用例 2: 区間 affine 変換・区間和

`range_affine_range_sum` のように、各要素 `x` に対して `x -> b*x+c` を作用させ、区間和を取りたい場合です。

```cpp
using mint=StaticModInt<998244353>;

struct Info{
    using value_type=pair<mint,mint>; // {sum,len}
    static value_type op(value_type a,value_type b){
        return {a.first+b.first,a.second+b.second};
    }
    static value_type e(){
        return {0,0};
    }
};

struct Tag{
    using lazy_type=pair<mint,mint>; // {b,c}
    static lazy_type Merge(lazy_type old_tag,lazy_type new_tag){
        return {new_tag.first*old_tag.first,new_tag.first*old_tag.second+new_tag.second};
    }
    static lazy_type id(){
        return {1,0};
    }
    static Info::value_type Apply(Info::value_type x,lazy_type f){
        return {x.first*f.first+x.second*f.second,x.second};
    }
};
```

このとき `value_type` に長さ `len` を持たせているのが重要です。
区間全体の和に `c` を足すには `len*c` が必要なので、`sum` だけでは `Apply` を書けません。
