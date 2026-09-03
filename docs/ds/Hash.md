---
title: hash_type
documentation_of: ../../ds/utility/Hash.hpp
---

# hash_type

`N` 個の値を並列に持つラッパー構造体です。
複数 base のハッシュ値をまとめて扱うときに使います。

## 型

```cpp
hash_type<T, N>
```

- `T` — 各要素の型（通常は `mod261_int` などの mod 型）
- `N` — 並列数（衝突率を下げたいときは 2〜3 が多い）

内部には `array<T,N>` が入っています。

## コンストラクタ

### `hash_type(long long x = 0)`

全要素を `T(x)` で初期化します。

### `hash_type(T x)`

全要素を `x` で初期化します。

## 演算子

`hash_type` どうし、または `hash_type` と `T` スカラーに対して以下が使えます。

| 演算子 | 動作 |
|--------|------|
| `+`, `-`, `*`, `/` | 要素ごとの四則演算 |
| `+=`, `-=`, `*=`, `/=` | 同上（in-place） |
| `==`, `!=`, `<`, `<=`, `>`, `>=` | `array` の比較（等価または辞書順） |
| `h[i]` | i 番目の要素へのアクセス |

## 静的メソッド

### `static const hash_type& hash_type<T,N>::get_base()`

各要素がランダムな素数（約 `2 〜 2e10` の範囲）である `hash_type` を返します。
最初の呼び出し時にのみ生成され、以降はキャッシュされます。

### `static hash_type hash_type<T,N>::get_rand()`

`long long` の非負の範囲から各成分を一様乱数で生成します。

## 境界・注意

- 衝突を避けるためには `T` に mod 型（例: `mod261_int`）を使うか、`N>=2` にするのが安全です。
- `T=long long` では 2 つのコンストラクタが同じシグネチャになり、テンプレートを実体化できません。`long long` を直接指定せず mod 型を使ってください。
- `get_base()` は実行のたびに同じ値を返します（static キャッシュ）。同一プログラム内では一定です。
- `hash_type` 自体はローリングハッシュの前処理を行いません。前処理ロジックはユーザーが書く必要があります。
- `operator[](i)` は `0<=i<N` を `assert` します。除算は `T` 側の除算が定義され、各除数が有効であることが前提です。

## 計算量

- 構築、四則演算、比較、`get_rand()`: `O(N)`
- `operator[]`: `O(1)`
- `get_base()`: 2 回目以降は `O(1)`。初回は `N` 個の素数を試し割りで探し、1 候補 `p` の判定に `O(sqrt(p))` かかります。

## 使用例: 文字列ローリングハッシュ（2-base）

```cpp
#include "ds/utility/Hash.hpp"
#include "math/modular/mod261.hpp"

using H = hash_type<mod261_int, 2>; // mod261_int で 2 本

H base = H::get_base(); // ランダムな 2 つの素数

// 前処理: prefix hash と power を計算
int n = s.size();
vc<H> h(n+1), pw(n+1, H(1));
for(int i=0;i<n;i++){
    pw[i+1] = pw[i] * base;
    h[i+1] = h[i] * base + H(s[i]);
}

// [l,r) のハッシュ
auto get = [&](int l, int r) -> H {
    return h[r] - h[l] * pw[r-l];
};

if(get(l1,r1) == get(l2,r2)){
    // ほぼ等しい（衝突確率は非常に低い）
}
```
