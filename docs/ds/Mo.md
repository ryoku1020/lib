---
title: mo
documentation_of: ../../ds/sequence/Mo.hpp
---

# mo

mo's algorithm の順序付けと実行部分をまとめた構造体です。
この実装ではクエリ区間は半開ではなく閉区間 `[l,r]` です。

## コンストラクタ

### `mo(int N, int Q)`

長さ `N` の列に対する、`Q` 個程度のクエリを処理するための順序付け器を作ります。
ブロック幅は内部で自動決定されます。

- 制約: `N>=0`, `Q>=0`
- 計算量: `O(1)`

## メソッド

### `void mo.push(int l, int r)`

閉区間 `[l,r]` のクエリを追加します。
追加順がそのままクエリ id になります。

- 制約: `0<=l<=r<N`

### `void mo.sort()`

クエリ順を mo 順に並べ替えます。
通常は `run` が内部で呼ぶので、明示的に呼ばなくても構いません。

- 計算量: `O(q log q)`（`q` は実際に追加したクエリ数）

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

## 計算量

`push` はならし `O(1)`、`sort` は `O(q log q)` です。`Q` に実際のクエリ数 `q` を渡し、各コールバックが `O(1)` なら、`run` 全体は標準的に `O((N+q)sqrt(q)+q log q)` です。

## 境界・注意

- この実装は `[l,r]` の閉区間です。
- `run` の初期区間は空で、内部状態は `nl=0, nr=-1` から始まります。
- `push` の実装上の `assert` は `r<=N` ですが、`r==N` を入れると `run` がインデックス `N` をコールバックに渡します。配列クエリでは `0<=l<=r<N` を守ってください。
- クエリが 0 個でも `run` は何も呼び出さず正常終了します。コンストラクタの `Q` は予約数ではなくブロック幅の調整に使うため、実数に合わせます。

## 使用例

```cpp
#include "ds/sequence/Mo.hpp"

mo mo(n,q);
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
