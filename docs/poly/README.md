---
title: 多項式 API | poly
documentation_of: ../../poly/base.hpp
keywords: fps, formal power series, interpolate, multipoint_evaluation, chirp_z, sparse_fps, taylor_shift
---

# 多項式・形式的冪級数 API

`poly/base.hpp` の `fps<mint>` を使う追加操作です。係数列は昇べき順（`f[i]` が `x^i` の係数）。FPS の演算は法 `mint::get_mod()` を持つ modint を想定します。

```cpp
#include "poly/base.hpp"
#include "poly/multipoint-evaluation.hpp"

using mint = static_modint<998244353>;
fps<mint> f{1, 2, 3}; // 1 + 2x + 3x^2
auto values = multipoint_evaluation(f, vector<mint>{0, 1, 2});
```

## 評価・補間

| API | 用途 | 計算量・条件 |
|---|---|---|
| `multipoint_evaluation(f, xs)` | `f(xs[i])` を同じ順序で返す | `O((n+m) log^2(n+m))` 級。法・NTT/FPS 乗算要件あり |
| `subproduct_tree<mint> st(n)` | `add(x)` で点を登録し、`calc(f)` で一括評価 | 構築後の問い合わせ点を追加する場合は新しい木を作る |
| `interpolate(xs, ys)` | `f(xs[i])=ys[i]` を満たす次数 `< n` の多項式 | `xs.size()==ys.size()`、x 座標は相異なること。重複時は導関数評価の除算が失敗 |
| `linear_interpolate(n, y, v)` | `y[i]=f(i)` (`0<=i<n`) から次数 `<n` の `f(v)` を返す | `y.size()==n`。連続整数点での評価。階乗逆元を使うため法が `n` 以上の素数であること |
| `geo_interporate(a,r,y)` | `y[i]=f(a*r^i)` を満たす係数列 | `r!=0` ではサンプル点が相異なり、補間で割る値が可逆であること。`r==0` は `y.size()>=2` かつ `a` が可逆な場合に限る特別枝で、先頭 2 点から一次式を返す。関数名は実装上 `geo_interporate`（typo 含む） |
| `shiftof_sampling_points(n,t,m,sample)` | `f(0)..f(n-1)` から `f(t)..f(t+m-1)` を返す | 次数 `< n` の多項式。`sample.size()==n` |
| `chirp_z(f,a,r,m)` | `f(a), f(ar), ..., f(ar^(m-1))` | `m>=0`。`r==0` は専用枝で `f(a),f(0),...`。それ以外は `r` の逆元を使うため可逆であること |

`geo_interporate` のヘッダは `chirp_z` を include していません。使う場合は `#include "poly/chirp-z.hpp"` を先に記述してください。これは現行実装の依存関係上の注意です。

## 多項式演算

- `taylor_shift(f,c)` は係数を変換し `f(x+c)` を返します。入力 vector を値渡しするため元の `f` は変わりません。FPS 乗算相当の `O(n log n)` 級。
- `prefixsum_poly(f)` は多項式値の prefix sum を表す多項式を返します。次数 `n-1` の入力に対して長さ `n+1` の係数列。Bernoulli 数と FPS 畳み込みを使います。
- `naive_mul(F,G)` は愚直な係数畳み込みで、時間 `O(|F||G|)`。両入力は空でないこと。`naive_div(F,G)` は `{商, 余り}` を返します。`G` は非零かつ空でない多項式であること。どちらも入力は値渡し。
- `all_prod(v)` は FPS のリストの積を返します。空リストでは `1`。
- `fpsfrac<mint>` は有理関数を分子・分母の FPS として保持する型です。メンバは `fps-frac.hpp` を参照してください。
- `power_sum(a,c,K)` は `res[k]=sum_i c[i]*a[i]^k` を `k=0..K` で返します。`a` と `c` は同じ長さ。時間は多項式積に依存します。

## 疎な形式的冪級数

`spfs<mint> = vector<pair<int,mint>>` は `{次数,係数}` の列です。

- `inv_sparse(n, f)`, `log_sparse(n,f)`, `exp_sparse(n,f)`, `pow_sparse(n,f,k)`, `sqrt_sparse(n,f)` は長さ `n` までの逆元・対数・指数・冪・平方根を返します。
- `sqrt_sparse` は解なしなら `nullopt`。他の関数は条件違反（例: `f[0]==0` の逆元、対数定数項、exp の定数項）を一般に検証しません。
- 入力次数は重複しない形にまとめ、次数・係数を昇順にしてください。計算量は疎項数 `s` と出力次数 `n` に対して概ね `O(ns)`、`pow_sparse` / `sqrt_sparse` は先頭次数に応じて再帰します。

## 有理関数係数列・その他

- `bostan_mori(P,Q,n)` などの線形漸化式係数抽出は [Bostan–Mori](../math/bostan-mori.md) を参照してください。
- `cinverse(f)` は FPS の逆合成、`power_projection(f,g,n,m)` は係数抽出用の変換を行います。次数・定数項制約が強いため、使う前に各関数の assert と実装コメントを確認してください。
- `sparse-fps.hpp` 以外の個別ファイル: `all-prod.hpp`, `chirp-z.hpp`, `cinverse.hpp`, `fps-frac.hpp`, `geo-interpolate.hpp`, `interpolate.hpp`, `linear-interpolate.hpp`, `multipoint-evaluation.hpp`, `naive-div.hpp`, `power-sum.hpp`, `prefixsum-poly.hpp`, `shift-of-sampling-points.hpp`, `taylor-shift.hpp`。

FPS の積が準線形時間で動くか、また法が NTT に適するかは `poly/base.hpp` の実装に従います。アルゴリズム名だけから他ライブラリの API や制約を推定しないでください。
