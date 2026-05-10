---
title: Manacher
documentation_of: ../../string/manacher.hpp
---

# Manacher

各位置を中心とする回文の半径を `O(|s|)` で求めます。
奇数長・偶数長の両方を 1 本の配列で扱います。

## 関数

### `vc<int> Manacher(String& s)`

長さ `2*|s|-1` の配列 `rad` を返します。
空文字列なら空配列、長さ 1 なら `{1}` を返します。

- 計算量: `O(|s|)`

## 出力の読み方

`rad[c]` は「拡張列での中心 `c` における回文半径」です。

| インデックス | 意味 | 元の中心 |
|---|---|---|
| `c = 2*i`（偶数） | `s[i]` が中心の奇数長回文の半径 | 文字中心 |
| `c = 2*i+1`（奇数） | `s[i]` と `s[i+1]` の間が中心の偶数長回文の半径 | 文字間中心 |

- `rad[2*i]` = k なら、`s[i-k .. i+k]` が最長の回文（長さ `2k+1`）
- `rad[2*i+1]` = k なら、`s[i-k+1 .. i+k]` が最長の回文（長さ `2k`）

## 区間 [l, r] が回文かどうか判定

```cpp
// s[l..r] が回文 ⟺ rad[l+r] * 2 >= r - l
bool is_palindrome(int l, int r) {
    return rad[l + r] * 2 >= r - l;
}
```

これは奇数長・偶数長どちらにも使えます。

## 使用例

```cpp
#include "string/manacher.hpp"

string s = "abacaba";
auto rad = Manacher(s);

// 各文字中心の最長回文長
for (int i = 0; i < (int)s.size(); i++) {
    int k = rad[2*i]; // 半径
    // s[i-k..i+k] が最長奇数長回文（長さ 2k+1）
}

// s[2..4] = "aca" が回文かチェック
int l = 2, r = 4;
bool ok = rad[l + r] * 2 >= r - l; // true

// 最長回文部分文字列の長さ
int ans = 0;
for (int c = 0; c < (int)rad.size(); c++) {
    ans = max(ans, rad[c] * 2 - (c % 2 == 0 ? 1 : 0));
}
```

## 注意

- 返り値の長さは `2*|s|-1`（空文字列は `{}`、長さ 1 は `{1}`）。
- `s[i]` は比較可能な任意の型の列に使えます（`string`, `vector<int>` など）。
