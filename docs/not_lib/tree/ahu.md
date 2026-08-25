---
title: AHU Algorithm (根付き木の同型判定)
documentation_of: ../../../.not_lib/tree/ahu.hpp
---

# AHU Algorithm

Aho, Hopcroft, Ullman によって提案された、根付き木の同型判定（tree Isomorphism）を行うためのアルゴリズムの実装です。
与えられた根付き木の構造を括弧の列 `(...)` で表現し、この文字列が一致するかどうかで木の同型判定が可能です。
※この実装はSuffix Array (`suffix_array`) を用いて部分木のソートを高速に行う工夫がされています。

## ahu

```cpp
string ahu(const tree& tree_, int root);
```

### 制約・引数
- `const tree& tree_`: 対象の木。
- `int root`: 木の根とする頂点のインデックス。

### 戻り値
- `string`: 根付き木の構造を一意に表す括弧列（例: `((()())())`）。
同型な（同じ構造を持つ）根付き木は同じ文字列になります。この文字列同士を比較することで木の同型判定が行えます。

### 計算量
- $O(N \log N)$ (Suffix Array の構築に依存)

## 境界・注意

- 根付き木として比較します。根を変えると同じ無根木でも表現が変わることがあります。
- `tree` は木であることを仮定します。

## 使用例

2 つの根付き木が同型かどうかを、括弧列を比較して判定します。

```cpp
tree t1(n),t2(n);
// 辺を追加

string a=ahu(t1,0);
string b=ahu(t2,0);

if(a==b){
    // 根 0 の根付き木として同型
}
```
