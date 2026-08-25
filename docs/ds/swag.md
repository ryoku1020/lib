---
title: sliding_window_aggregation
documentation_of: ../../ds/sequence/swag.hpp
---

# sliding_window_aggregation

SWAG (Sliding Window Aggregation) です。
両端に push/pop しながら、現在の列全体のモノイド積を amortized `O(1)` で取得できます。

## 要件

```cpp
struct X {
    using value_type = ...;
    static value_type op(value_type a, value_type b);
    static value_type e();
};
```

## `sliding_window_aggregation<X>`

両端キュー版です。左右どちらからでも push/pop できます。

### メソッド

#### `void swag.push_front(value_type x)`
#### `void swag.push_back(value_type x)`

左端・右端に 1 要素追加します。

- 計算量: amortized `O(1)`

#### `void swag.pop_front()`
#### `void swag.pop_back()`

左端・右端から 1 要素削除します。

- 制約: 対応する側が空でないこと（空のとき動作未定義）
- 計算量: amortized `O(1)`

#### `value_type swag.get_all()`

現在入っている列全体の `op(a[0], ..., a[n-1])` を返します。
列が空のとき `e()` を返します。

- 計算量: `O(1)`

## `one_way_sliding_window_aggregation<X>`

片方向（キュー）用途に最適化した版です。
`push_back` して `pop_front` するだけの場合はこちらが軽量です。

```cpp
one_way_sliding_window_aggregation<X> q;
q.push_back(x);
auto cur = q.get_all();
q.pop_front();
```

## 境界・注意

- 空のとき `pop_*` を呼ぶと動作未定義です（内部で `assert` はされません）。
- `get_all()` は空のとき `e()` を返します。
- `op` が非可換でも正しく動きます（SWAG は左右を分けて管理するため）。

## 使用例: 固定幅スライディングウィンドウの最小値

```cpp
#include "ds/sequence/swag.hpp"

struct X {
    using value_type = long long;
    static value_type op(value_type a, value_type b) { return min(a, b); }
    static value_type e() { return (long long)4e18; }
};

sliding_window_aggregation<X> swag;

// 幅 K のウィンドウを右にずらしながら最小値を取る
for (int i = 0; i < n; i++) {
    swag.push_back(a[i]);
    if (i >= k) swag.pop_front();
    if (i >= k - 1) {
        ans[i] = swag.get_all();
    }
}
```
