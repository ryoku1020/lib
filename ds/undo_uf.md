---
title: Undo UnionFind (Rollback付きUnion-Find)
documentation_of: ./undo_uf.hpp
---

# Undo UnionFind (Rollback付きUnion-Find)

要素の併合 (merge) と、直近の併合の取り消し (undo)、およびすべての併合状態のリセット (rollback) をサポートした Union-Find です。
経路圧縮を使わず、サイズによるマージのみを用いることで、各操作を $O(\log N)$ に抑えています。

## 使い方

```cpp
#include "ds/undo_uf.cpp"

undo_Unionfind uf(N);

// 要素 0 と 1 を併合
uf.merge(0, 1);

// 直近の操作を1回分取り消す (0と1の併合を取り消し)
uf.undo();

// 現在の状態を保存 (以降の undo はここまでの状態まで戻るようになる)
uf.save();

// セーブ時点まで状態を戻す
uf.rollback();
```

## メソッド

### `undo_Unionfind(int n)`
要素数 $n$ で初期化します。
- 計算量: $O(N)$

### `int root(int x)`
要素 $x$ の属する連結成分の根のインデックスを返します。
- 制約: $0 \le x < n$
- 計算量: $O(\log N)$

### `bool same(int x, int y)`
要素 $x$ と要素 $y$ が同じ連結成分に属しているかを判定します。
- 制約: $0 \le x, y < n$
- 計算量: $O(\log N)$

### `bool merge(int x, int y)`
要素 $x$ を含む連結成分と要素 $y$ を含む連結成分を併合します。
併合が行われた場合は `true` を、すでに同じ連結成分に属していた場合は `false` を返します。
同じ連結成分の場合でも履歴として操作は保存されるため、後の `undo` でこの呼び出し自体が「1操作」として適切に取り消されます。
- 制約: $0 \le x, y < n$
- 計算量: $O(\log N)$

### `int size(int x)`
要素 $x$ が属する連結成分のサイズ (要素数) を返します。
- 制約: $0 \le x < n$
- 計算量: $O(\log N)$

### `void save()`
履歴スタックを空にします。これ以降の `undo` や `rollback` 操作は、この呼び出し時点までの状態には戻らなくなります。現在の状態を確定したい場合に用います。
- 計算量: スタックの要素数に比例 ($O(M)$, ただし $M$ は保存されている履歴数)

### `void undo()`
直近に実行された `merge` (何も併合しなかった `merge` も含む) の効果を1回分取り消し、状態を1つ元に戻します。
- 計算量: $O(1)$

### `void rollback()`
履歴スタックに残っているすべての操作を取り消し、初期状態または最後に `save()` を呼び出した直後の状態まで戻します。
- 計算量: 取り消す履歴数に比例 ($O(K)$)
