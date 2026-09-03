---
title: Z Algorithm
documentation_of: ../../string/z-algorithm.hpp
---

# Z Algorithm

文字列 `s` に対して `z[i]=LCP(s,s[i:])` を求めます。
パターンマッチや prefix の一致長をまとめて取りたいときに使います。

## 使い方

```cpp
#include "string/z-algorithm.hpp"

string s="aabcaabxaaaz";
auto z=z_algorithm(s);

// z[0]=|s|
// z[4]=3 ("aab" が一致)
```

`pattern + '#' + text` に対して Z-algorithm をかけると、各位置でパターンと何文字一致するかが分かります。

```cpp
string p="aba",t="ababa";
string x=p+'#'+t;
auto z=z_algorithm(x);
for(int i=0;i<t.size();i++){
    if(z[p.size()+1+i]>=p.size()){
        // t[i..] から p が出現
    }
}
```

## 戻り値

- `vc<int> z_algorithm(String& s)`
  長さ `|s|` の配列を返します。
- `z[0]=|s|`
- `z[i]`
  `s` 全体と `s[i:]` の最長共通接頭辞長です。

## 計算量

- 時間 `O(|s|)`、返り値メモリ `O(|s|)`、返り値を除く追加メモリ `O(1)`

## 境界・注意

- `|s| >= 1` が必要です。空列では長さ 0 の配列に `dp[0]` を書くため、現在の実装では扱えません。
- `String` は `size()`, `s[i]`, 要素間の `==` を持つ列を想定しています。
- 関数は非 const 左辺値参照を取るため、列を変数に入れて渡します。
- 返り値は 0-indexed です。
- パターン検索で連結する区切り文字は、パターンにもテキストにも含まれない値を選んでください。

## 使用例

文字列 `t` の中にパターン `p` が現れる位置を列挙します。

```cpp
string p,t;
cin>>p>>t;

string s=p+"$"+t;
auto z=z_algorithm(s);

for(int i=0;i<(int)t.size();i++){
    if(z[p.size()+1+i]>=(int)p.size()){
        cout<<i<<"\n";
    }
}
```
