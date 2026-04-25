---
title: setreap
documentation_of: ../../ds/setreap.hpp
---

# setreap

ランダム優先度 treap による順序付き集合です。
重複なし集合として扱います。

## 主なメソッド

### `void st.insert(T x)`
### `void st.erase(T x)`
### `bool st.count(T x)`

挿入、削除、存在判定です。

### `T st.next(T x)`

`x` 以上の最小要素を返します。
存在しなければ `-1` です。

### `T st.prev(T x)`

`x` 未満の最大要素を返します。
存在しなければ `-1` です。

### `int st.bigger(T x)`
### `int st.smaller(T x)`
### `int st.range_count(T l, T r)`

個数クエリです。

### `T st.kth(int k)`

`k` 番目の要素を返します。
存在しなければ `-1` です。

### `int st.size()`

集合サイズです。

## 使用例

```cpp
setreap<int> st;
st.insert(5);
st.insert(2);
int x=st.next(3); // 5
```
