---
title: Aho-Corasick
documentation_of: ../../string/aho-corasick.hpp
---

# Aho-Corasick

複数パターンをまとめて trie に登録し、suffix link を張ったオートマトンです。
テキストを 1 文字ずつ読みながら、パターンの出現判定・出現回数集計・suffix link tree 上の DP に使えます。

## 型

```cpp
AhoCorasick<sigma, give_order>
```

- `sigma` — アルファベットサイズ（例: `26` for 英小文字）
- `give_order` — 文字を `[0, sigma)` に写す関数（例: `[](char c){ return c-'a'; }`）

## メソッド

### `int ac.add(String& s)`

文字列 `s` を trie に追加します。
新規に生成されたノード数を返します。
`s` の終端ノードのインデックスが `word` に追加されます（追加順）。

- 制約: `give_order(s[i])` が `[0, sigma)` に収まること
- 計算量: `O(|s|)`

### `void ac.build()`

suffix link を BFS で構築します。
`add` をすべて終えてから 1 度だけ呼んでください。

- 計算量: `O(sigma * |trie|)`

### `int ac.next(int x, Char c)`

ノード `x` にいる状態で文字 `c` を読んだ後の遷移先ノードを返します。
trie 遷移が存在しない場合は suffix link を辿り、遷移先がない場合は `root` を返します。
内部で `build()` を呼ぶので、事前に明示的に `build()` していなくても使えます。

- 制約: `give_order(c)` が `[0, sigma)` に収まること
- 計算量: `O(辿った suffix link の本数 + 1)`

### `int ac.size()`

trie のノード数を返します。

### `vc<int> ac.suffix_order()`

suffix link tree でトポロジカル順（葉から根方向）の頂点列を返します。
suffix link 親への集約 DP（出現回数の伝播など）に使います。

### `vvc<int> ac.suffix_inv()`

suffix link tree の子リストを返します。

## 主なメンバ

| メンバ | 説明 |
|--------|------|
| `child[v][c]` | ノード `v` から文字 `c` への trie 遷移。存在しなければ `-1` |
| `suffix[v]` | ノード `v` の suffix link |
| `depth[v]` | ノード `v` の trie 上の深さ |
| `word[i]` | `i` 番目に `add` した文字列の終端ノード id |
| `root` | 根ノード（= 0） |

## 境界・注意

- `next(x,c)` は suffix link を辿って遷移先を探します。
  `child[v][c] == -1` の遷移はオートマトンとしてあらかじめ補完されません。
- `build()` 前に `suffix` を使ってはいけません。
- `word[i]` は追加順のノード id です。同じ文字列を複数回 `add` すると同じノードが複数回記録されます。

## テキスト中のパターン出現を数える典型例

```cpp
#include "string/aho-corasick.hpp"

auto f = [](char c){ return c - 'a'; };
AhoCorasick<26, f> ac;

vc<string> patterns = {"he", "she", "hers"};
for (auto& p : patterns) ac.add(p);
ac.build();

// テキストを読んで各ノードの通過回数を集計
string text = "ushers";
vc<int> cnt(ac.size(), 0);
int v = ac.root;
for (char ch : text) {
    v = ac.next(v, ch);
    cnt[v]++;
}

// suffix link を使って出現回数を親に集約（葉から根方向）
auto order = ac.suffix_order();
for (int u : order) {
    if (ac.suffix[u] != u) cnt[ac.suffix[u]] += cnt[u];
}

// 各パターンの出現回数
for (int i = 0; i < (int)patterns.size(); i++) {
    cout << patterns[i] << ": " << cnt[ac.word[i]] << "\n";
}
```

