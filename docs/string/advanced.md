---
title: 文字列追加 API | KMP・Suffix Automaton
documentation_of: ../../string/kmp.hpp
keywords: prefix_function, period, find_pattern, suffix_automaton, wild_match, KMP
---

# 文字列追加 API

各文字列関数は入力を変更しません。位置は 0-indexed です。区間を返す機能では、ページに記す半開区間 `[l,r)` を使います。

## KMP

```cpp
#include "string/kmp.hpp"

string s = "ababab", p = "aba";
auto pi = prefix_function(s);
int per = period(s);             // 2
auto pos = find_pattern(s, p);   // {0,2}
```

- `prefix_function(s)` は `pi[i]` = `s[0..i]` の最長 proper border 長を返す。長さ `n`、時間 `O(n)`。
- `period(s)` は列全体を繰り返しで表す最小周期を返す。空列は 0。時間 `O(n)`。
- `find_pattern(s, pattern)` は一致開始位置を昇順で返す。空 pattern の場合、実装は文字位置 `[0,|s|]` を返す。時間 `O(|s|+|pattern|)`。
- `find_pattern` の第 3 テンプレート引数 `ban`（既定値 `'~'`）は実装内の区切り文字です。列要素に使われない値を選んでください。

## Suffix automaton

`suffix_automaton` は `string` を 1 文字ずつ `add(char)` で追加し、異なる部分文字列数や出現位置情報を扱う状態機械です。

```cpp
#include "string/suffix-automaton.hpp"

string s = "ababa";
suffix_automaton sam(s);
long long distinct = sam.number_substring();
```

`suffix_automaton(string s)` は構築と同時に終端状態数 `Esize` と suffix-link tree `g` を用意します。`number_substring()` は異なる部分文字列数を `long long` で返し、`in_substring(s)` は部分文字列の出現回数を返します。`kth_substring(k)` は辞書順 k 番目（0-indexed）の空でない部分文字列、`lcsusbstring(t)` は入力と `t` の最長共通部分文字列を返します。基本 `add(int c)` で追加する場合、`number_substring()` は使えますが、`Esize` / `g` を構築する文字列コンストラクタ後の処理は行われません。

状態数・構築時間は `O(n)`。

この実装の `give(char)` は `'a'..'z'` 以外も写像するため、英小文字限定と決めつけないでください。状態の `link`, `len`, `next` を直接利用する場合、クローン状態を含むため元の位置との 1:1 対応はありません。

## Wildcard match

`wild_match<TF>(s,t,wild)` は `t` の `wild` 文字を任意の 1 文字として `s` 内を検索し、一致開始位置を返します。

```cpp
#include "string/wild-match.hpp"
string text = "abacaba", pattern = "a?a";
auto pos = wild_match<3>(text, pattern, '?');
```

- wildcard は pattern 内だけで特別扱いされます。
- 返り値は一致する全開始位置。空 pattern の境界条件は利用前に確認してください。
- `TF` は乱数割り当てを再試行する回数です。modulus は内部で 998244353 に固定され、NTT 畳み込みを使います。
- 1回の照合衝突確率は小さいものの 0 ではなく、TF 回の独立した乱数再割り当てで偽一致の確率を下げます。決定的な完全一致判定ではありません。
- `n=|s|, m=|t|` として時間 `O(TF * n log n)`、作業領域 `O(n)`。

関連: [Z algorithm](z-algorithm.md) は prefix との一致長、[suffix array](lcpsuf.md) は全 suffix の辞書順、[Rolling Hash](rolling-hash.md) は区間一致判定向けです。
