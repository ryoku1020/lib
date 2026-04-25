---
title: DoublePriorityQueue
documentation_of: ../../ds/Doublepq.hpp
---

# DoublePriorityQueue

最小値と最大値を両方取り出せる priority queue です。
遅延削除で実装されています。

## メソッド

### `void pq.push(T x)`
### `T pq.front()`
### `T pq.back()`
### `T pq.pop_front()`
### `T pq.pop_back()`
### `int pq.size()`

## 使用例

```cpp
DoublePriorityQueue<int> pq;
pq.push(3);
pq.push(10);
auto mn=pq.front();
auto mx=pq.back();
```
