---
title: Lazy Segtree (遅延セグメント木)
documentation_of: ./lazy_seg.cpp
---

# Lazy Segtree (遅延セグメント木)

区間に対する作用 (遅延評価) と、区間に対する演算 (取得) を行えるセグメント木です。
要素のモノイド (`Info`) と、作用素のモノイド (`Tag`) を構造体で指定します。
区間は全て半開区間 $[l, r)$ の 0-indexed で扱います。

## 使い方

```cpp
#include "ds/lazy_seg.cpp"

// 値のモノイド
struct Info {
    using value_type = long long;
    static value_type op(value_type a, value_type b) { return min(a, b); }
    static value_type e() { return 1e18; }
};

// 作用素のモノイドと作用関数
struct Tag {
    using lazy_type = long long;
    static value_type Apply(value_type a, lazy_type b) {
        return a + b; // 区間加算
    }
    static lazy_type Merge(lazy_type a, lazy_type b) {
        return a + b; // 作用素のマージ
    }
    static lazy_type id() {
        return 0; // 恒等写像 (作用させても変化しない値)
    }
};

// 長さ N で初期化
lazy_segtree<Info, Tag> seg(N);

// 配列 A から初期化 O(N)
vector<long long> A(N, 0);
lazy_segtree<Info, Tag> seg_arr(N, A);

// 区間 [l, r) に作用素 x を適用 (区間加算など)
seg.apply(l, r, x);

// 区間 [l, r) の演算結果を取得 (区間最小値など)
long long res = seg.prod(l, r);

// 1点 i を直接値 x で上書き
seg.set(i, x);
```

## メソッド

### `lazy_segtree(int N)`
長さ $N$ で初期化します。内部的には最小の2冪のサイズが確保されます。
初期値は `Info::leaf()` が定義されていればそれが、なければ `Info::e()` がセットされます。
- 計算量: $O(N)$

### `lazy_segtree(int N, std::vector<value_type> A)`
長さ $N$ で初期化し、配列 `A` の値で初期化します。
- 計算量: $O(N)$

### `void apply(int l, int r, lazy_type x)`
半開区間 $[l, r)$ の各要素に作用素 `x` を適用します。
- 制約: $0 \le l \le r \le n$
- 計算量: $O(\log N)$

### `value_type prod(int l, int r)`
半開区間 $[l, r)$ の演算結果を返します。
- 制約: $0 \le l \le r \le n$
- 計算量: $O(\log N)$

### `void set(int i, value_type x)`
位置 $i$ の要素を直接 `x` に上書き変更し、遅延評価も整合性を保つよう更新します。
- 制約: $0 \le i < n$
- 計算量: $O(\log N)$

### `value_type all_prod()`
区間全体の演算結果を返します。
- 計算量: $O(1)$
