---
title: prefix-multicative helpers
documentation_of: ../../math/combinatorics/prefix-multicative.hpp
---

# prefix-multicative helpers

$n$ 以下の整数に関わる積性関数の総和を $O(n^{2/3})$ または $O(n^{3/4}/\log n)$ で計算する補助関数群です。
内部では **Lucy DP (min_info-25 篩の前半)** を利用しています。

## 関数

### `vc<ll> floors(ll n)`

$\lfloor n/k \rfloor$ が取りうるすべての値を昇順で返します。
返り値の長さは $O(\sqrt{n})$ です。

```cpp
auto v = floors(12);
// → {1, 2, 3, 4, 6, 12}
```

### `tuple<vc<T>,vc<int>,vc<ll>> lucy_dp<T>(ll n, F f, G g)`

min_info-25 篩の前半（Lucy DP）を実行します。

- `f(x)` : 篩う前の初期値。典型的には $\sum_{i=1}^{x} i^k$ のような整数全体の前計算可能な累積和
- `g(p)` : 素数 `p` で倍数を除くときの重み。$i^k$ の素数和なら $p^k$
- 返り値:
  - `vc<T> dp` : `dp[i]` = `floors(n)` の `i` 番目の値 $v$ に対する篩後の累積値。`f(1)` を含むため、素数だけの和が欲しい場合は通常 `f(1)` を引く
  - `vc<int> primes` : $\sqrt{n}$ 以下の素数リスト
  - `vc<ll> QN` : `floors(n)` の値リスト（添字の対応に使う）

### `mint black_algorithm<DP,F,G,H,mint>(ll n, F f, G g, H h)`

min_info-25 篩の後半（Black algorithm）を実行し、積性関数 $\sum_{i=1}^{n} f(i)$ を計算します。

- テンプレート引数 `DP` : Lucy DP の型
- `f(x)` / `g(x)` : Lucy DP と同じ
- `h(p, e)` : 素数冪 $p^e$ への寄与（例: $p^e - p^{e-1}$、`e=1` なら素数の寄与）

この実装では返り値型 `mint` を関数引数から推論できないため、`DP` だけでなく関数型と `mint` まで明示します。

```cpp
auto ans=black_algorithm<DP,decltype(f),decltype(g),decltype(h),mint>(n,f,g,h);
```

## 計算量

- `floors(n)`: 時間・メモリともに `O(sqrt(n))`
- `lucy_dp`: 時間 `O(n^(3/4)/log n)` 程度、メモリ `O(sqrt(n))`
- `black_algorithm`: Lucy DP と素数冪の列挙を合わせた Min_25 型の計算量。典型的な積性関数では時間 `O(n^(3/4)/log n)` 程度、メモリ `O(sqrt(n))`

`f`, `g`, `h` 1 回の演算を `O(1)` と数えています。

## 境界・注意

- `n >= 0` が必要です（`assert` あり）。`floors(0)` と `lucy_dp(0, ...)` の返す配列は空です。
- `black_algorithm` は `n >= 4` で使ってください。現在の実装は `n < 4` では素数リストが空のため常に `1` を返します。
- `sqrt(n)` を `int` で保持し、長さ `O(sqrt(n))` の配列を確保します。`sqrt(n)` が `int` と利用可能メモリに収まる必要があります。
- かなり高度な実装です。単に素数個数が必要なら `prime_counting` のようなラッパーを使ってください。
- `f`, `g`, `h` の設計は問題の積性関数に依存します。`h(p, 1)` は素数冪 `p^1 = p` での寄与を返す関数です。
- `DP` は加減算と `g(p)` との乗算を、`mint` は `DP` からの構築と四則演算をサポートする必要があります。

## 使用例: $n$ 以下の素数の個数

```cpp
#include "math/number_theory/prime-counting.hpp"

ll cnt = prime_counting(n);
```

`prime-counting.hpp` が `prefix-multicative.hpp` + `enumerate-floor.hpp` をラップしているので、
単に素数の個数が欲しいだけなら `prime_counting(n)` を使ってください。

## 使用例: $n$ 以下の素数の和

```cpp
#include "math/combinatorics/prefix-multicative.hpp"

using mint = static_modint<998244353>;

auto prefix_sum=[](ll x){
    return mint(x)*mint(x+1)/2; // 1+2+...+x
};
auto prime_weight=[](ll p){
    return mint(p);
};

// Lucy DP で「x 以下の素数の和」を求める
auto [dp, primes, QN] = lucy_dp<mint>(
    n,
    prefix_sum,
    prime_weight
);

// n >= 1。初期値に含めた 1 を除く
mint sum_of_primes=dp.back()-mint(1);
```
