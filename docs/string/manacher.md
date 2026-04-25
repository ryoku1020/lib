---
title: Manacher
documentation_of: ../../string/manacher.hpp
---

# Manacher

各位置を中心とする回文の半径を線形時間で求めます。
奇数長と偶数長をまとめて扱うため、実装内部で区切り文字を挟んでいます。

## 使い方

```cpp
#include "string/manacher.hpp"

string s="abacaba";
auto rad=Manacher(s);
```

例えば `s="abba"` のとき、返り値は長さ `2*|s|-1` の配列になります。
元の文字上の中心と文字の間の中心が交互に並びます。

- index `0,2,4,...` は文字中心
- index `1,3,5,...` は文字間中心

## 戻り値の見方

- `vc<int> Manacher(String& s)`
  長さ `2*|s|-1` の配列を返します。
- `res[c]`
  拡張後の列で中心 `c` における回文半径です。

実用上は次のように読むと便利です。

- `c=2*i`
  `s[i]` を中心とする奇数長回文の半径
- `c=2*i+1`
  `s[i]` と `s[i+1]` の間を中心とする偶数長回文の半径

## 例

```cpp
string s="abba";
auto rad=Manacher(s);

// 中心 1 と 2 の間に長さ 4 の回文 "abba" がある
// 偶数長中心 c=3 に対応する半径を見る
```

## 計算量

- `O(|s|)`

## 注意

- `s.size()==1` のときは `{1}` を返します。
- 返り値の添字は元の文字列添字とは一致しないので、中心の意味を意識して使います。
