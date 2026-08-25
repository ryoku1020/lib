---
title: node_pool
documentation_of: ../../ds/utility/node-pool.hpp
---

# node_pool

ノードのメモリプールです。
`new` / `delete` の代わりに使うことで、動的確保の定数倍を削減できます。

削除されたノードは空きスタックに積まれ、次の `get_new()` で再利用されます。

## テンプレートパラメータ

| パラメータ | 説明 |
|-----------|------|
| `T` | プールに格納するノードの型 |
| `ptr_t` | ノード ID の型（デフォルト: `int`）。`short` にするとメモリを節約できる場面もある |

## コンストラクタ

### `node_pool(int s = 4)`

初期容量 `s` のプールを作ります。
確保したノード数が容量を超えると自動的に 2 倍に拡張します（`grow()`）。

- 計算量: `O(s)`

## メソッド

### `T& pool[i]`

`pool.operator[](ptr_t i)` でノード `i` への参照を返します。

- 計算量: `O(1)`

### `ptr_t pool.get_new()`

新しいノードの ID を確保して返します。
空きスタック（`del` で返したノード）が存在する場合はそれを優先して返します。

- 計算量: `O(1)` amortized（容量拡張がなければ `O(1)`）

### `ptr_t pool.get_new(Args... args)`

`T(args...)` でコンストラクトしたノードの ID を返します。

- 計算量: `O(1)` amortized

### `void pool.del(ptr_t i)`

ノード `i` を解放し、空きスタックに返します。
**`pool[i]` の内容はそのまま残ります**（`T` のデストラクタは呼ばれません）。

- 計算量: `O(1)`

### `void pool.clear()`

全ノードをリセットします。`idx` を 1 に戻し、空きスタックをクリアします。
`pool` の内容はクリアされません。

- 計算量: `O(1)`

## 境界・注意

- ノード ID `0` は null ポインタ相当の番兵として使うことを想定しています（`idx` は `1` から始まる）。
- `del` は `T` のデストラクタを呼びません。ポインタなどリソースを持つ型を使う場合は手動で後始末してください。
- `clear()` 後も `pool[i]` の内容は残っています。再利用前に初期化が必要な場合は `get_new(args...)` で上書きするか、手動で初期化してください。

## 使用例

```cpp
#include "ds/utility/node-pool.hpp"

struct node {
    int val, left, right;
    node() : val(0), left(0), right(0) {}
    node(int v) : val(v), left(0), right(0) {}
};

node_pool<node> pool(1 << 20);

// 新ノードを確保
int root = pool.get_new(42);
pool[root].left = pool.get_new();

// ノードを解放
pool.del(pool[root].left);
pool[root].left = 0;

// 再確保（解放したスロットが再利用される）
int new_node = pool.get_new(99);
```
