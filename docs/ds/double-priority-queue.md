---
title: double_priority_queue
documentation_of: ../../ds/double-priority-queue.hpp
---

# double_priority_queue

最小値と最大値を両方取り出せる priority queue です。
遅延削除で実装されています。

## コンストラクタ

### `double_priority_queue<T>()`

空のキューを作成します。

## メソッド

### `void pq.push(T x)`

値 `x` を追加します。

- 計算量: `O(log n)`

### `T pq.front()`

最小値を返します（削除しない）。

- 制約: キューが空でないこと。空のとき `assert` で停止。
- 計算量: `O(log n)` amortized

### `T pq.back()`

最大値を返します（削除しない）。

- 制約: キューが空でないこと。空のとき `assert` で停止。
- 計算量: `O(log n)` amortized

### `T pq.pop_front()`

最小値を取り出して返します。

- 制約: キューが空でないこと。空のとき `assert` で停止。
- 計算量: `O(log n)` amortized

### `T pq.pop_back()`

最大値を取り出して返します。

- 制約: キューが空でないこと。空のとき `assert` で停止。
- 計算量: `O(log n)` amortized

### `int pq.size()`

現在の要素数を返します。

- 計算量: `O(1)`

## 境界・注意

- 内部は遅延削除で実装されており、`front`/`back`/`pop_*` 呼び出し時に不要ノードを削除します。
- `size()` は定数時間ですが、`front`/`back` は amortized です。

## 使用例

```cpp
#include "ds/double-priority-queue.hpp"

double_priority_queue<int> pq;
pq.push(3);
pq.push(10);
pq.push(1);

auto mn = pq.front();    // 1（最小値）
auto mx = pq.back();     // 10（最大値）
auto lo = pq.pop_front(); // 1 を取り出す
auto hi = pq.pop_back();  // 10 を取り出す
// 残りは {3}
```
