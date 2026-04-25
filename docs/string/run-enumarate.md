---
title: Run Enumerate
documentation_of: ../../string/run-enumarate.hpp
---

# Run Enumerate

文字列中の run を列挙する関数です。
ここで run とは、周期 `t` を持ち、長さが `2t` 以上ある極大な区間を指します。

## 使い方

```cpp
#include "string/run-enumarate.hpp"

string s="ababababa";
auto runs=RunEnumerate(s);

for(auto [t,l,r]:runs){
    // s[l,r) が周期 t を持つ run
}
```

## 戻り値

- `vc<array<int,3>> RunEnumerate(string s)`
  各要素は `{t,l,r}` です。

各成分の意味は次の通りです。

- `t`
  run の周期
- `l`
  区間の左端
- `r`
  区間の右端の次

つまり `s[l:r)` が周期 `t` を持つ run です。

## 典型例

```cpp
for(auto [t,l,r]:RunEnumerate(s)){
    if(t==1){
        // 同じ文字が連続している run
    }
    if(r-l>=10){
        // 十分長い周期区間だけ使う
    }
}
```

## 計算量

- 典型的には `O(n log n)` 相当で run を列挙します。

## 注意

- 戻り値の順序は保証されません。
- 実装は `ZAlgorithm` を内部で利用しています。
