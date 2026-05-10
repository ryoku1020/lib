---
title: setreap
documentation_of: ../../ds/setreap.hpp
---

# setreap

ランダム優先度 treap による順序付き集合（重複なし）です。

## 型

```cpp
setreap<T>
```

- `T` — 要素の型。非負整数型を推奨（`int`, `long long`）。
  負の値を挿入すると `assert` で停止します。

## コンストラクタ

### `setreap<T>()`

空の集合を作成します。

### `void st.build(vc<T> v)`

配列 `v` から集合を構築します（重複は自動除去）。
既存の内容はリセットされます。

- 計算量: `O(n log n)`

## メソッド

### `void st.insert(T val)`

`val` を集合に追加します。既に存在する場合は何もしません。

- 制約: `val >= 0`
- 計算量: `O(log n)`

### `void st.erase(T val)`

`val` を集合から削除します。存在しない場合は何もしません。

- 制約: `val >= 0`
- 計算量: `O(log n)`

### `bool st.count(T val)`

`val` が集合に含まれるなら `true`、そうでなければ `false` を返します。

- 計算量: `O(log n)`

### `T st.next(T val)`

`val` 以上の最小要素を返します。
存在しない場合は `-1` を返します。

- 注意: `-1` が有効な戻り値として解釈されるのは `T` が非負整数のときのみです。

### `T st.prev(T val)`

`val` 未満の最大要素を返します。
存在しない場合は `-1` を返します。

### `int st.bigger(T val)`

`val` 以上の要素数（`[val, ∞)` に属する個数）を返します。

### `int st.smaller(T val)`

`val` 未満の要素数（`(-∞, val)` に属する個数）を返します。

### `int st.range_count(T l, T r)`

半開区間 `[l, r)` に含まれる要素数を返します。

- 制約: `l <= r`

### `T st.kth(int k)`

昇順で `k` 番目（0-indexed）の要素を返します。
`k >= size()` のとき `-1` を返します。

- 制約: `k >= 0`

### `int st.size()`

集合の要素数を返します。

## 使用例

```cpp
#include "ds/setreap.hpp"

setreap<int> st;
st.insert(5);
st.insert(2);
st.insert(8);

bool ok = st.count(5);    // true
int nx = st.next(3);      // 5  （3以上の最小）
int pv = st.prev(5);      // 2  （5未満の最大）
int bg = st.bigger(4);    // 2  （4以上は 5, 8）
int sm = st.smaller(5);   // 1  （5未満は 2）
int rc = st.range_count(2, 6); // 2  （[2,6) は 2, 5）
int k0 = st.kth(0);       // 2  （昇順0番目）

st.erase(5);
int nx2 = st.next(3);     // 8
int nx3 = st.next(100);   // -1（存在しない）
```

## 注意

- `val >= 0` が必須です（内部で `assert`）。負の値は使えません。
- `next` / `prev` / `kth` の「見つからない場合は `-1`」は、`T` が符号あり整数かつ非負の値のみを格納する場合にのみ正しく機能します。
- `range_count(l, r)` は半開区間 `[l, r)` です（右端を含まない）。
