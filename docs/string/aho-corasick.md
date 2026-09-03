---
title: Aho-Corasick
documentation_of: ../../string/aho-corasick.hpp
---

# Aho-Corasick

複数パターンをまとめて trie に登録し、suffix link を張ったオートマトンです。
テキストを 1 文字ずつ読みながら、パターンの出現判定・出現回数集計・suffix link tree 上の DP に使えます。

## 型

```cpp
aho_corasick<sigma, give_order>
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


### `int ac.next(int x, Char c)`

ノード `x` にいる状態で文字 `c` を読んだ後の遷移先ノードを返します。
trie 遷移が存在しない場合は suffix link を辿り、遷移先がない場合は `root` を返します。
内部で `build()` を呼ぶので、事前に明示的に `build()` していなくても使えます。

- 制約: `give_order(c)` が `[0, sigma)` に収まること

### `int ac.size()`

trie のノード数を返します。

### `vc<int> ac.suffix_order()`

suffix link tree で根から子へ向かう順の頂点列を返します。先頭は根です。
親から子へ配る DP にはそのまま、子から親への集約には逆順で使います。

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

## 計算量

trie のノード数を `V`、最大パターン長を `L`、テキスト長を `T` とします。

- `add(s)`: 時間 `O(|s|)`、新規ノードと再帰スタックに最大 `O(sigma*|s|)` / `O(|s|)` メモリ
- `build()`: 通常 `O(sigma*V)`、suffix link を逐次探索する現在の実装の最悪時は `O(sigma*V+V*L)`
- `next(x,c)`: 最悪 `O(L)`。根からテキストを連続走査する一連の呼び出しは合計 `O(T)` に償却される
- `size()`: `O(1)`
- `suffix_order()`, `suffix_inv()`: `build()` 済みなら時間・返り値メモリともに `O(V)`
- 本体のメモリ: `O(sigma*V)`

## 境界・注意

- `next(x,c)` は suffix link を辿って遷移先を探します。
  `child[v][c] == -1` の遷移はオートマトンとしてあらかじめ補完されません。
- `add` / `next` に渡す文字はすべて `give_order(c)` が `[0,sigma)` に入る必要があります（`assert` あり）。
- `add` は非 const 左辺値参照を取るため、文字列を変数に入れて渡します。空パターンも追加でき、その終端は根になります。
- `build()` 前に `suffix` を直接使ってはいけません。`next`, `suffix_order`, `suffix_inv` は必要なら自動で `build()` します。
- `add()` を一度でも呼ぶと未構築状態へ戻ります。再び検索する際は自動または明示的に再構築されます。
- `word[i]` は追加順のノード id です。同じ文字列を複数回 `add` すると同じノードが複数回記録されます。

## 使用例: テキスト中のパターン出現回数

```cpp
#include "string/aho-corasick.hpp"

constexpr auto f=[](char c){return c-'a';};
aho_corasick<26, f> ac;

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

// suffix link を使って出現回数を子から親へ集約
auto order = ac.suffix_order();
for (auto it=order.rbegin();it!=order.rend();++it) {
    int u=*it;
    if (ac.suffix[u] != u) cnt[ac.suffix[u]] += cnt[u];
}

// 各パターンの出現回数
for (int i = 0; i < (int)patterns.size(); i++) {
    cout << patterns[i] << ": " << cnt[ac.word[i]] << "\n";
}
```
