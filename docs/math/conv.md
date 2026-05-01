---
title: Convolution
documentation_of: ../../math/conv.hpp
---

# Convolution

ACL ベースの NTT / 数論補助関数です。
主に畳み込みに使いますが、同じヘッダに `pow_mod`, `inv_mod`, `crt`, `floor_sum` も入っています。

## 畳み込み

### `vector<mint> convolution(const vector<mint>& a, const vector<mint>& b)`

modint 上の畳み込みを返します。
結果の長さは `a.size()+b.size()-1` です。

- 計算量: `O((n+m)log(n+m))`

### `vector<T> convolution(const vector<T>& a, const vector<T>& b)`

整数列を一度 modint に載せて畳み込む版です。
テンプレート引数 `T` は mod に収まる整数を想定しています。

### `vector<long long> convolution_ll(const vector<long long>& a, const vector<long long>& b)`

64bit 整数列の畳み込みを CRT 復元で返します。

### `vector<long long> convolution_ll(const vector<long long>& a, const vector<long long>& b, long long MOD)`

畳み込み結果を `MOD` で割ったものを返します。

## 使用例 1: modint 畳み込み

```cpp
#include "math/conv.hpp"
#include "math/static-mod-int.hpp"

using mint=StaticModInt<998244353>;

vector<mint> a={1,2,3};
vector<mint> b={4,5,6};
auto c=convolution(a,b);
```

## 使用例 2: 整数列の畳み込み

```cpp
vector<long long> a={1,2,3};
vector<long long> b={4,5,6};

auto c=convolution_ll(a,b);
auto d=convolution_ll(a,b,1000000007LL);
```

## その他の関数

### `long long pow_mod(long long x, long long n, int m)`

`x^n mod m` を返します。

### `long long inv_mod(long long x, long long m)`

`x mod m` の逆元を返します。
存在することを仮定しています。

### `pair<long long,long long> crt(const vector<long long>& r, const vector<long long>& m)`

中国剰余定理です。
`x ≡ r[i] (mod m[i])` を満たす解を `{x,lcm}` で返します。
解が存在しないときは `{0,0}` です。

### `long long floor_sum(long long n, long long m, long long a, long long b)`

`sum_{i=0}^{n-1} floor((a*i+b)/m)` を返します。

## 注意

- `convolution(const vector<mint>&, ...)` は NTT 可能な modint を想定しています。
- 小さい入力では内部で naive 畳み込みに落ちます。
