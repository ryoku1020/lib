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
auto runs=run_enumerate(s);

for(auto [t,l,r]:runs){
    // s[l,r) が周期 t を持つ run
}
```

## 戻り値

- `vc<array<int,3>> run_enumerate(string s)`
  各要素は `{t,l,r}` です。

各成分の意味は次の通りです。

- `t`
  run の周期
- `l`
  区間の左端
- `r`
  区間の右端の次

つまり `s[l:r)` が周期 `t` を持つ run です。

## 計算量

- 時間 `O(n log n)`、返り値と作業領域のメモリ `O(n)` です。

## 境界・注意

- 空文字列には空配列を返します。長さは `INT_MAX` 以下でなければなりません（`assert` あり）。
- 内部で区切り文字 `'#'` を挿入するため、入力には `'#'` を含めないでください。また、末尾判定が `s[s.size()] == '\0'` を利用するため、埋め込み NUL を含まない通常のテキスト文字列を想定しています。
- 戻り値の順序は保証されません。
- 同じ極大区間に複数の周期が見つかった場合、最小の周期だけを返します。
- 実装は `z_algorithm` を内部で利用しています。

## 使用例

```cpp
for(auto [t,l,r]:run_enumerate(s)){
    if(t==1){
        // 同じ文字が連続している run
    }
    if(r-l>=10){
        // 十分長い周期区間だけ使う
    }
}
```
