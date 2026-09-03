---
title: Convolution
documentation_of: ../../math/convolution/conv.hpp
---

# Convolution

ACL ベースの NTT / 数論補助関数です。
主に畳み込みに使いますが、同じヘッダに `pow_mod`, `inv_mod`, `crt`, `floor_sum` も入っています。

## 畳み込み

### `vector<mint> convolution(const vector<mint>& a, const vector<mint>& b)`

modint 上の畳み込みを返します。
結果の長さは `a.size()+b.size()-1` です。

- 計算量: `O((n+m)log(n+m))`

### `vector<T> convolution<mod>(const vector<T>& a, const vector<T>& b)`

整数列を一度 modint に載せて畳み込む版です。
`T` は整数型で、各要素を `mod` で正規化した畳み込みの剰余を `[0,mod)` の `T` で返します。
`mod` のデフォルトは `998244353` です。

### `vector<long long> convolution_ll(const vector<long long>& a, const vector<long long>& b)`

64bit 整数列の畳み込みを crt 復元で返します。

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

## 計算量

入力長を `n`, `m`、`L` を `n+m-1` 以上の最小の 2 のべき乗とします。

- 各 `convolution`: `min(n,m) <= 60` なら時間 `O(nm)`、それ以外は時間 `O(L log L)`。メモリ `O(L)`
- `convolution_ll`: 3 回の NTT を行い、時間 `O(L log L)`、メモリ `O(L)`
- `pow_mod(x,n,m)`: 時間 `O(log n)`、追加メモリ `O(1)`
- `inv_mod(x,m)`: 時間 `O(log m)`、追加メモリ `O(1)`
- `crt(r,m)`: 合同式の本数を `k` として時間 `O(k log M)`、追加メモリ `O(1)`。`M` は途中の法の大きさ
- `floor_sum`: 時間 `O(log m)`、追加メモリ `O(1)`

## 境界・注意

- いずれの畳み込みも、一方でも空なら `{}` を返します。
- modint 版と整数剰余版は、`L` が法 `mod-1` を割り切る NTT friendly な法を要求します（小さい入力でも事前に `assert` されます）。
- 整数剰余版は整数畳み込みそのものではなく、各係数を `mod` で割った非負剰余を返します。
- `convolution_ll` は `n+m-1 <= 2^24` を要求し、真の各係数が `long long` に収まる場合に厳密値を復元します。
- `pow_mod` は `n >= 0`, `m >= 1`、`inv_mod` は `m >= 1` かつ `gcd(x,m) == 1` を要求します（`assert` あり）。
- `crt` は `r.size() == m.size()` と全ての `m[i] >= 1` を要求します。返す最小非負解と法の最小公倍数が `long long` に収まる必要があります。空の連立には `{0,1}` を返します。
- `floor_sum` は `0 <= n < 2^32`, `1 <= m < 2^32` を要求します。`a`, `b` は負でも構いませんが、答えが `long long` に収まる必要があります。

## 使用例 1: modint 畳み込み

```cpp
#include "math/convolution/conv.hpp"
#include "math/modular/static-mod-int.hpp"

using mint=static_modint<998244353>;

vector<mint> a={1,2,3};
vector<mint> b={4,5,6};
auto c=convolution(a,b);
```

## 使用例 2: 整数列の畳み込み

```cpp
vector<long long> a={1,2,3};
vector<long long> b={4,5,6};

auto c=convolution_ll(a,b);

// 998244353 を法とする剰余畳み込み
auto d=atcoder::convolution<998244353>(a,b);
```
