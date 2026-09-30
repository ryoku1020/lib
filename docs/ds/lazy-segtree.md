---
title: 遅延セグメント木 | lazy_segtree
documentation_of: ../../ds/segment_tree/lazy-segtree.hpp
keywords: 区間更新, 区間和, 区間最小値, lazy_segtree, apply, prod, max_right
---

# 遅延セグメント木 (`lazy_segtree`)

区間更新と区間集約を行うセグメント木です。値モノイドと作用を `acted` 型にまとめて渡します。1 点更新・区間積のみなら [`segtree`](segtree.md)、区間作用と一点取得だけなら [`dual_segtree`](dual-segtree.md) が簡潔です。

```cpp
#include "ds/segment_tree/lazy-segtree.hpp"
#include "ds/act/add.hpp"

using A = add_sum<long long>;
lazy_segtree<A> seg(5, 0LL); // 5 個の 0
seg.apply(1, 4, 3);          // [1,4) に +3
long long s = seg.prod(0, 5); // 9
```

## 要件: `acted`

テンプレートは `lazy_segtree<acted, beats=false>` です。`acted` は次を提供します。

```cpp
struct acted {
    struct info {
        using value_type = long long;
        static value_type op(value_type a, value_type b) { return a + b; }
        static value_type id() { return 0; }
    };
    struct tag {
        using value_type = long long;
        static value_type op(value_type old_tag, value_type new_tag) {
            return old_tag + new_tag;
        }
        static value_type id() { return 0; }
        static constexpr bool commute = true; // 任意
    };
    using value_type = info::value_type;
    using lazy_type = tag::value_type;
    static value_type act(value_type value, lazy_type f, int length) {
        return value + f * length;
    }
};
```

- `info::op` は結合的で、`info::id()` が単位元であること。
- `tag::op(old,new)` は古い作用の後に新しい作用を適用した合成、`tag::id()` は恒等作用です。
- `acted::act(value,f,len)` は区間全体の集約値に作用します。区間和を扱うなら通常、作用を反映するために長さ `len` を使います。
- `tag::commute` は任意です。`true` を指定するなら作用タグ同士が可換でなければなりません。既定は `false` です。
- `beats=true` は `act` 後の値が `fail()` を提供する Segment Tree Beats 型用です。通常は省略します。

## コンストラクタ

- `lazy_segtree<N>(int n, value_type leaf = info::id())` は全要素を `leaf` にする。`O(n)`。
- `lazy_segtree<N>(int n, vc<value_type> a)` は `a` で初期化する。`a` が短ければ残りは `info::id()` で埋め、長ければ `2^ceil(log2(n))` 要素まで読み取るため `a.size()<=n` を守る。`O(n)`。
- `lazy_segtree<N>(int n, F f)` は `a[i]=f(i)` で初期化する。`O(n)`。

## メソッド

| 呼び出し | 動作・返り値 | 計算量 |
|---|---|---|
| `seg.set(p,x)` | `a[p]=x` に上書き | `O(log n)` |
| `seg.prod(l,r)` | `info::op(a[l],...,a[r-1])`。空区間は `info::id()` | `O(log n)` |
| `seg.apply(l,r,f)` | `[l,r)` の各値へ `f` を適用 | `O(log n)` |
| `seg.applyat(p,f)` | 位置 `p` の値へ `f` を適用 | `O(log n)` |
| `seg.all_prod()` | 全体 `[0,n)` の集約値 | `O(1)` |
| `seg.max_right(l,pred)` | `pred(prod(l,r))` が真の最大 `r` | `O(log n)` |
| `seg.min_left(r,pred)` | `pred(prod(l,r))` が真の最小 `l` | `O(log n)` |

全区間引数は 0-indexed 半開区間 `[l,r)`。`max_right` / `min_left` では `pred(info::id())==true` かつ判定が単調である必要があります。実装に `get(p)` はありません。1 点値は `prod(p,p+1)` で取得します。

### 合成順序

ノードの pending tag に新しいタグを重ねる箇所は `tag::op(old_tag,new_tag)` です。非可換な作用では順序が重要です。例えば affine タグ `{a,b}` が `x -> a*x+b` を表すなら、古い `{a,b}` の後に新しい `{c,d}` を適用した合成は `{c*a,c*b+d}` です。

## 使用例: 区間代入・区間和

用意済みの action 型を利用できます。

```cpp
#include "ds/act/assign.hpp"
#include "ds/segment_tree/lazy-segtree.hpp"

using A = assign_sum<long long>;
lazy_segtree<A> seg(8, 0LL);
seg.apply(2, 6, optional<long long>{5}); // [2,6) を 5 に代入
auto sum = seg.prod(0, 8);               // 20
```

`assign_sum<T>` の tag は `optional<T>` です。`nullopt` は何もしない作用、値ありは代入です。

## メモリ・注意

- 時間は各区間操作 `O(log n)`、構築 `O(n)`。配列領域は `O(n)`。
- `n==0` では `all_prod()` が根要素 `info::id()` を返します。
- 区間外の padding 葉の長さは 0 です。作用が長さを使う場合、`len==0` への作用も恒等である必要があります。
- `act` が任意区間の集約値に対して正しく作用する（分配則を満たす）必要があります。
- `commute=true` のとき実装は通常の push を省略します。タグが実際に可換でない場合、誤った結果になります。
