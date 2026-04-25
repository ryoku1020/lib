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
auto z=ZAlgorithm(s);

// z[0]=|s|
// z[4]=3 ("aab" が一致)
```

`pattern + '#' + text` に対して Z-algorithm をかけると、各位置でパターンと何文字一致するかが分かります。

```cpp
string p="aba",t="ababa";
string x=p+'#'+t;
auto z=ZAlgorithm(x);
for(int i=0;i<t.size();i++){
    if(z[p.size()+1+i]>=p.size()){
        // t[i..] から p が出現
    }
}
```

## 戻り値

- `vc<int> ZAlgorithm(String& s)`
  長さ `|s|` の配列を返します。
- `z[0]=|s|`
- `z[i]`
  `s` 全体と `s[i:]` の最長共通接頭辞長です。

## 計算量

- `O(|s|)`

## 注意

- `String` は `s[i]` でアクセスできる列を想定しています。
- 返り値は 0-indexed です。
