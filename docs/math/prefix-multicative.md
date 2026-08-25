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

### `tuple<vc<T>,vc<int>,vc<ll>> lucy_dp(ll n, F f, G g)`

min_info-25 篩の前半（Lucy DP）を実行します。

- `f(x)` : $x$ が素数のとき素数への寄与の「初期値」（例: $x$ 自身や $x^k$）
- `g(x)` : 素数の寄与が 1 段階上に伝播するときの乗数（例: 倍数除去の係数）
- 返り値:
  - `vc<T> dp` : `dp[i]` = `floors(n)` の `i` 番目の値 $v$ に対して「$\le v$ の素数への寄与の総和」
  - `vc<int> primes` : $\sqrt{n}$ 以下の素数リスト
  - `vc<ll> QN` : `floors(n)` の値リスト（添字の対応に使う）

### `mint black_algorithm<DP>(ll n, F f, G g, H h)`

min_info-25 篩の後半（Black algorithm）を実行し、積性関数 $\sum_{i=1}^{n} f(i)$ を計算します。

- テンプレート引数 `DP` : Lucy DP の型
- `f(x)` / `g(x)` : Lucy DP と同じ
- `h(p, e)` : 素数冪 $p^e$ への寄与（例: $p^e - p^{e-1}$、`e=1` なら素数の寄与）

## 境界・注意

- かなり高度な実装です。使い方に慣れるまでは `prime_counting` などのラッパーを使う方が無難です。
- `f`, `g`, `h` の設計は問題の積性関数に依存します。`h(p, 1)` は素数冪 `p^1 = p` での寄与を返す関数です。
- `black_algorithm` のテンプレート引数 `<mint>` は戻り値の型で、`DP` 型と分けて指定できます。

## 使用例: $n$ 以下の素数の個数

```cpp
#include "math/combinatorics/prefix-multicative.hpp"
#include "math/number_theory/enumerate-floor.hpp"

// prime_counting(n) を直接使う方が楽
ll cnt = prime_counting(n);
```

`prime-counting.hpp` が `prefix-multicative.hpp` + `enumerate-floor.hpp` をラップしているので、
単に素数の個数が欲しいだけなら `prime_counting(n)` を使ってください。

## 使用例: $n$ 以下の素数の和

```cpp
#include "math/combinatorics/prefix-multicative.hpp"

using mint = static_modint<998244353>;

// f(x) = x (素数 x の寄与は x 自身)
// g(x) = 1 (係数は 1)
// h(p, e) = p^e * (1 - p) ... 等

// Lucy DP で「x 以下の素数の和」を求める
auto [dp, primes, QN] = lucy_dp<mint>(
    n,
    [](ll x){ return mint(x); }, // 初期値 = x
    [](ll x){ return mint(1); }  // 係数 = 1
);

// dp.back() が「n 以下の素数の和」
mint sum_of_primes = dp.back() - mint(1); // 1 を除く
```
