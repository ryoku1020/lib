---
title: Binary Trie
documentation_of: ../../ds/BinaryTrie.hpp
---

# Binary Trie

非負整数の多重集合を管理し、全体のXOR操作や最小値の取得などを高速に行うための2進トライ木 (Binary Trie) です。
※ 現在の実装はテンプレートや型定義(`T`, `depth`)がコード上に暗黙に依存しているため、使用時に適宜型の修正や外部変数の定義が必要になる場合があります。

## BinaryTrie

### メンバ変数
- `int all_size`: トライ木に格納されている要素の総数
- `T offset`: 現在の全体にかかっているXORオフセット
- `Node* root`: トライ木の根ノード

### メソッド

- `BinaryTrie()`
  空のトライ木を初期化します。

- `void insert(T val, int x = 1)`
  値 `val` を `x` 個追加します。`val` は非負整数である必要があります。`x` に負の値を指定することで削除の動作を行わせることも可能です(サイズが負にならないように注意してください)。
  計算量: $O(\text{depth})$

- `void all_xor(T x)`
  木に含まれる全ての要素に対して `x` をXOR演算します。この操作は遅延的に `offset` に適用されるため $O(1)$ で完了します。
  計算量: $O(1)$

- `T find_min()`
  現在の木に含まれる要素（`offset` によるXOR演算適用後の値）のうち、最小のものを返します。
  ※ 木が空の場合（`all_size == 0`）は `assert` で停止します。
  計算量: $O(\text{depth})$
