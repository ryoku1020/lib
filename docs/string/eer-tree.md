---
title: eer_tree
documentation_of: ../../string/eer-tree.hpp
---

# eer_tree (Palindrome tree)

回文部分文字列を管理するトライ木（Palindrome tree / Eertree）です。
文字列を左から 1 文字ずつ追加しながら、最長回文接尾辞や各回文の情報を追えます。

## 型

```cpp
eer_tree<sigma>
```

- `sigma` — アルファベットサイズ（英小文字なら `26`）

## メソッド

### `void et.build(string s, char CHRMIN)`

文字列 `s` を左から順に追加し、Palindrome tree を構築します。

- 各文字は `s[i] - CHRMIN` で `[0, sigma)` に写す必要があります
- 計算量: `O(|s|)`

## 主なメンバ

| メンバ | 説明 |
|--------|------|
| `len[v]` | ノード `v` が表す回文の長さ |
| `suffix[v]` | ノード `v` の最長真回文接尾辞へのリンク |
| `suffix_tree_depth[v]` | suffix link を辿る深さ（その回文の palindromic suffix の個数） |
| `child[v][c]` | 文字 `c` を両端に付けてできる回文への遷移。-∞ なら未生成 |
| `pali_node[i]` | `s[0..i]` の最長回文接尾辞を表すノード id（`i = 0..n-1`） |

### 特殊ノード

- ノード 0: `len = -1`（虚根。長さ奇数の回文生成に使われる）
- ノード 1: `len = 0`（空文字列の回文）

### 異なる回文部分文字列の個数

```cpp
int distinct_palindromes = et.child.size() - 2; // 2 つの根を除く
```

## 境界・注意

- `child[v][c]` の「存在しない」状態は `-1e9`（整数として大きな負の値）です。
  存在判定は `child[v][c] >= 0` で行えます。
- `sigma` は実際に使う文字数に合わせて設定してください。大きすぎるとメモリを消費します。
- `build` は内部で `static int id` を使うため、複数の `eer_tree` インスタンスを作ると id が累積します。
  単一インスタンスで使う想定です。

## 使用例

```cpp
#include "string/eer-tree.hpp"

string s = "abacaba";
eer_tree<26> et;
et.build(s, 'a');

// 各位置 i での最長回文接尾辞の長さ
for (int i = 0; i < (int)s.size(); i++) {
    int node = et.pali_node[i];
    cout << "s[0.." << i << "] の最長回文接尾辞: 長さ " << et.len[node] << "\n";
}

// 異なる回文部分文字列の個数
int cnt = (int)et.child.size() - 2;

// suffix_tree_depth を使って palindromic suffix の個数を数える（各位置で）
for (int i = 0; i < (int)s.size(); i++) {
    int node = et.pali_node[i];
    int k = et.suffix_tree_depth[node]; // s[0..i] に出現する異なる回文接尾辞の個数
}
```
