---
title: SlidingWindowAggregation
documentation_of: ../../ds/swag.hpp
---

# SlidingWindowAggregation

SWAG です。
両端 push/pop をしながら、現在の列全体のモノイド積を amortized `O(1)` で取得できます。

## 要件

```cpp
struct X{
    using value_type=...;
    static value_type op(value_type a,value_type b);
    static value_type e();
};
```

## `SlidingWindowAggregation<X>`

両端キュー版です。

### メソッド

#### `void swag.push_front(value_type x)`
#### `void swag.push_back(value_type x)`

左右どちらかに 1 要素追加します。

#### `void swag.pop_front()`
#### `void swag.pop_back()`

左右どちらかから 1 要素削除します。

#### `value_type swag.get_all()`

現在入っている列全体の積を返します。

## 使用例

```cpp
#include "ds/swag.hpp"

struct X{
    using value_type=long long;
    static value_type op(value_type a,value_type b){ return a+b; }
    static value_type e(){ return 0; }
};

SlidingWindowAggregation<X> swag;
swag.push_back(3);
swag.push_back(5);
swag.push_front(2);
auto s=swag.get_all(); // 10
swag.pop_front();
```

## `OneWaySlidingWindowAggregation<X>`

キュー用途に寄せた片方向版です。
`push_back`, `push_front`, `pop_front`, `get_all` を持ちます。

### 使用例

```cpp
OneWaySlidingWindowAggregation<X> q;
q.push_back(x);
q.push_back(y);
auto cur=q.get_all();
q.pop_front();
```

## 注意

- 空状態で `pop_*` は呼ばない想定です。
- `get_all()` は空のとき `e()` を返します。
