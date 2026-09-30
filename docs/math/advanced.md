---
title: 数学追加 API | 二項係数・整数論
documentation_of: ../../math/combinatorics/counting.hpp
keywords: binom, crt, factorize, is_prime, floor_sum, discrete_log, primitive_root, multiple_zeta, nimber
---

# 数学追加 API

よく使う二項係数・整数論関数の索引です。式や法の条件が異なるため、似た名前でも関数ごとの前提を確認してください。

## 二項係数

`binom<mint>` は static 関数で階乗テーブルを共有します。

```cpp
using mint = static_modint<998244353>;
binom<mint>::build(100000); // 任意。C/P から必要分は自動構築
mint c = binom<mint>::C(n, k);
mint f = binom<mint>::fact(n);
```

- `fact(n)`, `invfact(n)`, `inv(n)`, `C(n,k)`, `iC(n,k)`, `P(n,k)`, `H(n,k)` を提供。`C` は二項係数、`P` は順列数、`H` は重複組合せ。
- テーブル拡張は `O(n)` 時間・`O(n)` 静的メモリ。以後の取得は `O(1)`。
- 階乗逆元方式のため、法が素数なら `n < mod` を守ります。非 modint の `mint` は `1/i` が存在する範囲でのみ使えます。
- `C` / `iC` は範囲外の `k` に 0 を返します。`H(a,b)` は実装上 `C(a+b-1,b)`。

他の組合せ API: `arbitrary_binom` は法 `m` の二項係数を素因数冪ごとに計算し CRT 結合します。`build(m)` 後に `query(n,k)` を呼びます。`m` の各素因数冪 `p^e` が `INT_MAX` 以下である制約があり、前処理領域は法の因子に依存します。`big_binom<mint>(n,k)` は `C(n,k)` を保持し、`inc_n`, `dec_n`, `inc_k`, `dec_k`, `push_front/back`, `pop_front/back` で近傍の引数を更新します。`dec_n` は `n>0`、`dec_k` / pop は `k>0` が必要です。

## 整数論

| API | 動作・返り値 | 条件 / 計算量 |
|---|---|---|
| `factorize(n)` | `(素因数, 指数)` を昇順で返す | 正整数 `n`。Miller–Rabin + Pollard rho、確率的な実行時間 |
| `is_prime(n)` | 素数なら 1 | signed 64-bit 範囲を想定。Miller–Rabin |
| `divisors(n)` | 正の約数を列挙 | `n>=1`。約数個数を `τ(n)` とすると `O(τ(n))` 出力 |
| `floor_sum(n,m,a,b)` | `sum(i=0..n-1) floor((a*i+b)/m)` | `0<=n<2^32`, `1<=m<2^32`; `O(log m)` |
| `discrete_log(c,x,y,m)` | `c*x^k ≡ y (mod m)` を満たす最小 `k`、なければ `-1` | 正の法、内部逆元が必要な枝あり。一般に BSGS `O(sqrt(m))` 時間・領域 |
| `primitive_root(p)` | 素数 `p` の原始根を返す | `p>=2`。乱数試行回数は期待計算量 |
| `validsegment(a,b,l,r)` | `a*t+b ∈ [l,r]` を満たす整数 `t` の閉区間 `{lo,hi}` | 解なしは `{0,-1}`、`a==0` かつ成立時は `{-inf,inf}` |
| `enumerate_pow<mint>(N,k)` | `f[i]=i^k` を `0..N` で返す | 線形篩で `O(N)` 時間・領域 |

`crt(r0,r1)` は `{剰余,法}` を2本結合して `{x,lcm}` を返し、矛盾時 `{ -1,-1 }`。法は 0 でない整数で、互いに素でなくても整合すれば解けます。複数式版 `crt(vector<pair<T,T>>)` も同じ規則です。中間積が `T` を越えないようにしてください。

`multiple_zeta`, `multiple_mobius`, `divisor_zeta`, `divisor_mobius` は添字 `1..n` の配列を in-place 変換します（`a[0]` はそのまま）。各変換は `O(n log log n)` 程度、篩を共有して使います。別の順序で呼ぶと同じ結果にはなりません。

## 離散対数の一括計算

- `multidiscrete(p,g,a)` は素数法 `p`、生成元 `g` に対する各 `a[i]` の離散対数 `x` (`g^x ≡ a[i] mod p`) を返します。存在しない要素は `-1`。Baby-step giant-step で `O(sqrt(p*|a|))` 程度の時間・`O(sqrt(p*|a|))` 領域。
- `findlog(p,g,a)` はより大きい `p` 用の randomized algorithm です。素数 `p` と原始根 `g` が必要で、同じ返り値規則。期待計算量であり、再現性・最悪時間の保証はありません。
- これらの入力 `a[i]` は `[0,p)` の剰余代表に正規化してください。`dynamic_modint64::raw` は範囲検査付きで正規化しません。

## 追加

- `binom_as2d<mint>(n,m)` は `0<=i<=n, 0<=j<=m` の Pascal 表を返します。`O(nm)` 時間・領域。
- `stirling1_as2d`, `stirling2_as2d` は第一種・第二種 Stirling 数の表を返します。引数・境界は各ヘッダを参照してください。
- `counting.hpp` は `partition_function`, `stirling1/2`, `montmort_number`, `bell_number` などを提供します。FPS 演算を使う関数は modint と `poly/base.hpp` の形式的冪級数実装を要します。
- `nimber` は nimber 上の `+,-,*,/` を実装する型です。整数 modint と乗算定義が異なります。
- `bernoulli<mint>(n)` は `B_0..B_{n-1}` を昇順に返します。この実装は `B_1=-1/2` の符号規約です。FPS 逆元を使うため、`mint` は必要な階乗が可逆な法を使います。
- `extgcdasexp(a,b,c)` は `ax+by=c` の整数解を表す `{{dx,x0},{dy,y0}}` を返し、`x=dx*t+x0`, `y=dy*t+y0` が全解です。解なしなら全成分に `-inf<T>` を返します。`a==b==0` は assert 条件違反。
- `modint_vp<mint> x = a` は `a` の `mint::get_mod()` による p 進付値 `x.v` と、単元部分 `x.x` を保持します。`x *= integer`, `x /= integer` は整数因子を操作し、`x.val()` は `v==0` なら単元部、`v>0` なら 0 を返します。`v<0` の `val()` は assert に失敗します。法は素数を想定します。
- `counting_spanning_tree<mint>(g)` は無向グラフの spanning tree 数を Matrix-Tree 定理で数え、`mint` を返します。重みは使わず、多重辺は別辺として数えます。計算量 `O(V^3)`、連結でない場合は 0。
- `detx(m0,m1)` は正方行列に対する `det(m0+x*m1)` の係数列を `fps<T>` で返します。体上の modint と `m0`,`m1` の同じサイズが必要です。乱数 shift を最大 2 回試し、両方で必要な pivot が得られない場合はゼロ多項式を返す可能性があります。
- `convolutionp(a,b,p)` は長さ `p` の列を、法 `p` の非零剰余の乗法群を使って畳み込みます。`p` は素数、`a.size()==b.size()==p`、係数 `mint` の NTT 畳み込みが使えることが必要です。通常の添字加算の巡回畳み込みとは別です。

関連: [modint](static-mod-int.md) · [形式的冪級数](fps.md) · [素数カウント](prime-counting.md) · [床関数列挙](enumerate-floor.md)
