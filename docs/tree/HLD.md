---
title: Heavy-Light Decomposition (HL分解)
---

# Heavy-Light Decomposition (HL分解)

> **注意**: `tree/hld.hpp` は存在しません。
> HLD 機能は [`tree/base.hpp`](base.md) の `tree` クラスに統合されています。

HL分解の API については [`docs/tree/base.md`](base.md) を参照してください。

## 主な API (tree クラス)

| メソッド | 説明 |
|---------|------|
| `tree.lca(a, b)` | LCA を返す |
| `tree.dist(a, b)` | 辺数距離を返す |
| `tree.jumpup(a, k)` | `a` の k 個上の祖先 |
| `tree.jump(s, t, k)` | s→t パス上で s から距離 k の頂点 |
| `tree.query(s, t)` | s→t パスを in 配列上の区間列に分解 |

## 境界・注意

- このページは移行案内です。対応する `tree/hld.hpp` は存在しません。
- HLD の実装と詳しい境界条件は [tree](base.md) にまとめています。
- `tree.query(s,t)` の返り値は閉区間ベースです。セグ木に渡すときは `[min(l,r),max(l,r)+1)` に変換します。

## 使用例

```cpp
#include "tree/base.hpp"

tree tree(n);
for(int i=0;i<n-1;i++){
    INT(u,v); u--; v--;
    tree.add_edge(u,v);
}
tree.build(0); // 根 0 で構築

// LCA
int l = tree.lca(u, v);

// パスをセグ木クエリへ変換
for(auto [ql, qr] : tree.query(s, t)){
    // in[ql] <= in[qr] であれば [ql, qr] を左から右
    // in[ql] >  in[qr] であれば [qr, ql] を右から左 (非可換演算に注意)
    auto res = seg.prod(min(ql,qr), max(ql,qr)+1);
    // ...
}
```

詳細は [`docs/tree/base.md`](base.md) を参照してください。
