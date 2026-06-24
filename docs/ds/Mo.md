---
title: Mo
documentation_of: ../../ds/mo.hpp
---

# Mo

Mo's algorithm の順序付けと実行部分をまとめた構造体です。
この実装ではクエリ区間は半開ではなく閉区間 `[l,r]` です。

## コンストラクタ

### `Mo(int N, int Q)`

長さ `N` の列に対する、`Q` 個程度のクエリを処理するための順序付け器を作ります。
ブロック幅は内部で自動決定されます。

## メソッド

### `void mo.push(int l, int r)`

閉区間 `[l,r]` のクエリを追加します。
追加順がそのままクエリ id になります。

- 制約: `0<=l<=r<N`

### `void mo.Sort()`

クエリ順を Mo 順に並べ替えます。
通常は `run` が内部で呼ぶので、明示的に呼ばなくても構いません。

### `void mo.run(addleft, addright, eraseleft, eraseright, answer)`

現在区間を伸縮させながら全クエリを処理します。

- `addleft(i)`
  左端を 1 つ広げて `i` を追加
- `addright(i)`
  右端を 1 つ広げて `i` を追加
- `eraseleft(i)`
  左端 `i` を削除
- `eraseright(i)`
  右端 `i` を削除
- `answer(id)`
  クエリ id の答えを確定

## 境界・注意

- この実装は `[l,r]` の閉区間です。
- `run` の初期区間は空で、内部状態は `nl=0, nr=-1` から始まります。

## 使用例

```cpp
#include "ds/mo.hpp"

Mo mo(n,q);
for(int i=0;i<q;i++){
    mo.push(l[i],r[i]); // [l,r]
}

vector<long long> ans(q);
mo.run(
    [&](int i){ add(a[i]); },
    [&](int i){ add(a[i]); },
    [&](int i){ del(a[i]); },
    [&](int i){ del(a[i]); },
    [&](int id){ ans[id]=cur; }
);
```

