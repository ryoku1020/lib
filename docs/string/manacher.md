---
title: manacher
documentation_of: ../../string/manacher.hpp
---

# manacher

各位置を中心とする最長回文の長さを `O(|s|)` で求めます。
奇数長・偶数長の両方を 1 本の配列で扱います。

## 関数

### `vc<int> manacher(String& s)`

長さ `2*|s|-1` の配列 `rad` を返します。
空文字列なら空配列、長さ 1 なら `{1}` を返します。

- 計算量: `O(|s|)`

## 出力の読み方

`rad[c]` は中心 `c` における最長回文の **元の列上での長さ** です。

| インデックス | 意味 | 元の中心 |
|---|---|---|
| `c = 2*i`（偶数） | `s[i]` が中心の最長奇数長回文の長さ | 文字中心 |
| `c = 2*i+1`（奇数） | `s[i]` と `s[i+1]` の間が中心の最長偶数長回文の長さ | 文字間中心 |

- `rad[2*i] = 2*k+1` なら、`s[i-k .. i+k]` が最長の回文
- `rad[2*i+1] = 2*k` なら、`s[i-k+1 .. i+k]` が最長の回文

## 区間 [l, r] が回文かどうか判定

```cpp
// s[l..r] が回文 <=> その中心の最長回文が区間長以上
bool is_palindrome(int l, int r) {
    return rad[l+r]>=r-l+1;
}
```

これは奇数長・偶数長どちらにも使えます。

## 計算量

時間 `O(|s|)`、返り値と作業配列のメモリ `O(|s|)` です。

## 境界・注意

- 返り値の長さは `2*|s|-1`（空文字列は `{}`、長さ 1 は `{1}`）。
- `|s| <= INT_MAX/2` が必要です（`assert` あり）。
- 要素は値を保ったまま `int` に変換できる必要があります。内部の区切り値として `INT_MIN` を使うため、要素に `INT_MIN` を含めないでください。通常の `string` や、この値を含まない `vector<int>` に使えます。
- 関数は非 const 左辺値参照を取るため、列を変数に入れて渡します。

## 使用例

```cpp
#include "string/manacher.hpp"

string s = "abacaba";
auto rad = manacher(s);

// 各文字中心の最長回文長
for (int i = 0; i < (int)s.size(); i++) {
    int len = rad[2*i];
    // s[i-len/2..i+len/2] が最長奇数長回文
}

// s[2..4] = "aca" が回文かチェック
int l = 2, r = 4;
bool ok = rad[l+r]>=r-l+1; // true

// 最長回文部分文字列の長さ
int ans=rad.empty()?0:*max_element(rad.begin(),rad.end());
```
