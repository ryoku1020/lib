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
- グラフ入力
  `readgraph`, `readtree`

## 境界・注意

- `using namespace std;` を含みます。
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
