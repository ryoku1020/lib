---
title: template.hpp
documentation_of: ../template.hpp
---

# template.hpp

このライブラリ全体の土台になる共通テンプレートです。
型エイリアス、ループマクロ、入出力、`chmin` / `chmax`、整数 utilities などがまとまっています。

## よく使うもの

```cpp
INT(n,m);
VC(int,a,n);

ll s=sum(a);
auto ps=presum(a);

chmax(s,100LL);
PRT("answer",s);
```

## 主な内容

- 型エイリアス
  `ll`, `ull`, `ld`, `pii`, `pll`, `vc<T>`, `vvc<T>`
- ループマクロ
  `rep`, `REP`, `drep`, `DREP`
- 入出力
  `INT`, `LL`, `STR`, `VC`, `VVC`, `PRT`
- 補助関数
  `chmin`, `chmax`, `floor`, `ceil`, `bmod`, `divmod`, `isqrt`, `popcount`, `sum`, `presum`, `subset`, `pow`

## 計算量

`n` は列の長さ、`H` と `W` は二次元列の縦横、`k` は集合を表すビット列の立っているビット数とします。

| 関数・マクロ | 時間計算量 | 追加領域 | 備考 |
|---|---:|---:|---|
| `chmin`, `chmax`, `floor`, `ceil`, `bmod`, `divmod`, `popcount` | `O(1)` | `O(1)` | 組み込み整数型を想定 |
| `sum`, `max`, `min` | `O(n)` | `O(1)` | `sum` の返り値型はテンプレート引数 `L` |
| `presum` | `O(n)` | `O(n)` | 長さ `n+1` の累積和を返す |
| `trans` | `O(HW)` | `O(HW)` | 転置した新しい二次元列を返す |
| `subset` | `O(2^k)` | `O(2^k)` | `0` を含む全部分集合を列挙 |
| `pow(a,b)` | `O(log b)` | `O(1)` | 二分累乗法、剰余は取らない |

入出力マクロの時間は読み書きする要素数に比例します。

## 境界・注意

- `using namespace std;` を含みます。
- C++20 の機能を利用しているため、`-std=c++20` 以降でコンパイルします。
- `floor`, `ceil`, `bmod`, `divmod` の除数は `0` にできません。特に `ceil(x,y)` は正の `y` を想定しています。
- `max(vector)` / `min(vector)` と `trans` は空でない列を前提とします。`trans` に渡す二次元列は全行を同じ長さにしてください。
- `isqrt(x)` は非負整数、`pow(a,b)` は `b >= 0` を前提とします。演算結果が型の範囲を超える場合の保護はありません。
- `subset(S)` は `S` の立っているビット数に対して指数個の要素を生成します。大きな集合には向きません。
- `sum` と `presum` の既定の累積型は `long long` です。和がその範囲を超える場合はテンプレート引数でより広い型を指定します。
- `template.hpp` 自体がかなり大きいので、ドキュメントでは全要素を列挙せず、特によく使うものに絞っています。

## 使用例

入力・集計・出力を短く書きます。

```cpp
#include "template.hpp"

int main(){
    INT(n);
    VC(ll,a,n);

    ll ans=sum(a);
    PRT(ans);
}
```
