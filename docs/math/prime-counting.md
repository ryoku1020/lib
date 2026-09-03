---
title: prime-counting
documentation_of: ../../math/number_theory/prime-counting.hpp
---

# prime-counting

`pi(n)`、つまり `n` 以下の素数の個数を求めます。
`floor(n/k)` の distinct な値をまとめて扱うことで、高速に素数個数を数えています。

## 使い方

```cpp
#include "math/number_theory/prime-counting.hpp"

cout<<prime_counting(10)<<"\n";   // 4
cout<<prime_counting(100)<<"\n";  // 25
```

## メソッド

- `ll prime_counting(ll n)`
  `n` 以下の素数の個数を返します。

## 計算量

- 時間はおおよそ `O(n^{3/4}/log n)`、メモリは `O(sqrt(n))` です。

## 境界・注意

- `n >= 1` の `ll` を渡してください。実装の `assert` は `n >= 0` ですが、`n == 0` では空配列の `back()` を参照します。
- `sqrt(n)` を添字・配列長に使うため、利用可能メモリに収まる必要があります。
- 内部で [enumerate-floor](./enumerate-floor.md) の `floors` を使っています。

## 使用例

区間 `(L,R]` に含まれる素数の個数を求めます。

```cpp
long long L,R;
cin>>L>>R;

long long left_count=(L==0?0:prime_counting(L));
long long ans=prime_counting(R)-left_count; // R >= 1
cout<<ans<<"\n";
```
