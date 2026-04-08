---
title: Segtree (セグメント木)
documentation_of: ../../ds/seg.hpp
---

# Segtree (セグメント木)

モノイドを乗せることができる、ボトムアップ実装のセグメント木です。
一点更新、区間積 (演算の適用)、二分探索 (`max_right`, `min_left`) を $O(\log N)$ で行います。
区間は全て 0-indexed で、半開区間 $[l, r)$ で指定します。

## 使い方

```cpp
#include "ds/seg.cpp"

// 載せるモノイドの情報を構造体で定義
struct Info {
    using value_type = long long;
    // 結合法則を満たす二項演算
    static value_type op(value_type a, value_type b) {
        return max(a, b);
    }
    // 単位元
    static value_type e() {
        return -1e18; // 十分小さい値
    }
    // 葉の初期化用 (segtree(int n) で呼ばれる)
    static value_type leaf() {
        return e();
    }
};

// 要素数 N で初期化 (値は全て Info::leaf() となる)
segtree<Info> seg(N);

// 配列や関数から初期化 (O(N))
auto f = [&](int i) -> long long {
    return A[i];
};
segtree<Info> seg2(N, f);

// i 番目の要素を x に更新
seg.set(i, x);

// 区間 [l, r) の演算結果を取得
long long res = seg.prod(l, r);

// 二分探索: L を左端とし、f(seg.prod(L, R)) が true を満たす最大の R を取得
auto check = [&](long long x) { return x < 100; };
int r = seg.max_right(L, check);
```

## メソッド

### `segtree(int n = 0)`
要素数 $n$ のセグメント木を構築します。各要素は `Info::leaf()` で初期化されます。内部では $n$ 以上の最小の2冪のサイズ $N$ で確保されます。
- 計算量: $O(N)$

### `template<class F> segtree(int n, F f)`
要素数 $n$ のセグメント木を構築し、初期値を関数 `f` で与えます。
$i$ 番目 ($0 \le i < n$) の要素は `f(i)` で初期化されます。
- 計算量: $O(N)$

### `void set(int i, value_type val)`
$i$ 番目 (0-indexed) の要素を `val` に更新し、木を再計算します。
- 制約: $0 \le i < n$
- 計算量: $O(\log N)$

### `value_type prod(int l, int r)`
半開区間 $[l, r)$ の演算結果 `op(a[l], a[l+1], ..., a[r-1])` を返します。
$l = r$ の場合は単位元 `e()` を返します。
- 制約: $0 \le l \le r \le n$
- 計算量: $O(\log N)$

### `value_type all_prod()`
区間 $[0, n)$ の演算結果を返します。
- 計算量: $O(1)$

### `template<class F> int max_right(int L, F f)`
左端 `L` を固定したとき、`f(prod(L, R)) == true` となる最大の右端 `R` を返します。
- 制約: `f(e()) == true` であること。$0 \le L \le n$
- 計算量: $O(\log N)$

### `template<class F> int min_left(int R, F f)`
右端 `R` を固定したとき、`f(prod(L, R)) == true` となる最小の左端 `L` を返します。
- 制約: `f(e()) == true` であること。$0 \le R \le n$
- 計算量: $O(\log N)$
