---
title: golden_search
documentation_of: ../../math/golden-search.hpp
---

# golden_search

離散区間 `[l,r]` で単峰な関数の最良値を探索するための関数です。
最小化・最大化のどちらにも使え、返り値は `{best_value,best_index}` です。

## 使い方

```cpp
#include "math/golden-search.hpp"

auto f=[&](long long x){
    return (x-7)*(x-7);
};

auto [val,arg]=golden_search<long long,long long>(0,20,f,(long long)4e18);
// arg=7, val=0
```

最大化したい場合は比較関数を変えます。

```cpp
auto g=[&](long long x){ return -1LL*(x-7)*(x-7); };
auto [val,arg]=golden_search<long long,long long>(0,20,g,(long long)-4e18,greater<long long>());
```

## メソッド

- `auto golden_search(T l,T r,F& get_value,G weakest,Compare Comp=Compare())`
  区間 `[l,r]` 上で最良の値とその位置を返します。

## 引数

- `l`, `r`
  探索する整数区間です。両端を含みます。
- `get_value`
  値を返す関数です。
- `weakest`
  区間外を読んだときの番兵値です。最小化なら十分大きい値、最大化なら十分小さい値を渡します。
- `Comp`
  比較関数です。デフォルトは `less` なので最小化です。

## 計算量

区間幅を `W = r-l+1` とすると、`get_value` の呼び出し回数は `O(log W)`、追加メモリは `O(1)` です。
`get_value` 1 回の計算量を `C` とすれば全体は `O(C log W)` です。

## 境界・注意

- `l <= r` が必要です。1 点区間でもその点を 1 回評価します。
- `Comp=less<G>` なら値が一度減少してから増加する離散単峰性、`greater<G>` なら一度増加してから減少する離散単峰性を仮定します。
- `weakest` は区間内のどの候補よりも弱い番兵値にしてください。最小化なら十分大きい値、最大化なら十分小さい値です。
- 同値の場合は index が小さい方を返します。
- `get_value` は非 const 左辺値参照で受け取るため、ラムダや関数オブジェクトを変数に入れて渡します。
- 内部で `l-1`, `r-l+2` などを計算します。これらと目的関数の計算が `T` / `G` の範囲を超えない区間を指定してください。

## 使用例

整数区間上の凸なコスト関数を最小化します。

```cpp
auto cost=[&](long long x){
    return (x-a)*(x-a)+b;
};

auto [best,arg]=golden_search<long long,long long>(0,1000000,cost,(long long)4e18);
cout<<arg<<" "<<best<<"\n";
```
