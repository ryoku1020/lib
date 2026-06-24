---
title: SparseTable
documentation_of: ../../ds/sparse-table.hpp
---

# SparseTable

冪等なモノイドに対する静的 RMQ 用データ構造です。
前計算 `O(n log n)`、区間クエリ `O(1)` で処理できます。

## 要件

```cpp
struct X{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

- `op` は結合法則を満たし、かつ `min` のような冪等演算を想定しています。

## コンストラクタ

### `SparseTable(int N)`

長さ `N` のテーブルを作ります。
`set` で値を入れたあと `build` します。

## メソッド

### `void st.set(int i, V x)`

位置 `i` の初期値を `x` にします。

- 制約: `0<=i<n`

### `void st.build()`

前計算を行います。

- 計算量: `O(n log n)`

### `V st.prod(int l, int r)`

`op(a[l],...,a[r-1])` を返します。
`l==r` のときは `e()` を返します。

- 制約: `0<=l<=r<=n`
- 計算量: `O(1)`

## 境界・注意

- 更新はできません。静的配列専用です。
- `prod` が `O(1)` で正しく動くのは、通常は `min` / `max` / `gcd` のような冪等演算のときです。

## 使用例

```cpp
#include "ds/sparse-table.hpp"

struct X{
    using value_type=int;
    static value_type op(value_type a,value_type b){
        return min(a,b);
    }
    static value_type e(){
        return (int)1e9;
    }
};

SparseTable<X> st(n);
for(int i=0;i<n;i++)st.set(i,a[i]);
st.build();

auto mn=st.prod(l,r);
```

