---
title: hash
documentation_of: ../../ds/utility/hash.hpp
---

# hash

`N` 個の値を並列に持つラッパー構造体です。
複数 base のハッシュ値をまとめて扱うときに使います。

## 型

```cpp
hash<T, N>
```

- `T` — 各要素の型（通常は mod 型や `long long`）
- `N` — 並列数（衝突率を下げたいときは 2〜3 が多い）

`value_type` は `hash<T,N>` 自体です。
内部には `array<T,N>` が入っています。

## コンストラクタ

### `hash(long long x = 0)`

全要素を `T(x)` で初期化します。

### `hash(T x)`

全要素を `x` で初期化します。

## 演算子

`hash` どうし、または `hash` と `T` スカラーに対して以下が使えます。

| 演算子 | 動作 |
|--------|------|
| `+`, `-`, `*`, `/` | 要素ごとの四則演算 |
| `+=`, `-=`, `*=`, `/=` | 同上（in-place） |
| `==`, `!=` | 全要素が等しいか |
| `h[i]` | i 番目の要素へのアクセス |

## 静的メソッド

### `static const hash& hash<T,N>::get_base()`

各要素がランダムな素数（約 `2 〜 2e10` の範囲）である `hash` を返します。
最初の呼び出し時にのみ生成され、以降はキャッシュされます。

## 境界・注意

- 衝突を避けるためには `T` に mod 型（例: `mod261_int`）を使うか、`N>=2` にするのが安全です。
- `get_base()` は実行のたびに同じ値を返します（static キャッシュ）。同一プログラム内では一定です。
- `hash` 自体はローリングハッシュの前処理を行いません。前処理ロジックはユーザーが書く必要があります。

## 使用例: 文字列ローリングハッシュ（2-base）

```cpp
#include "ds/utility/Hash.hpp"
// T に mod 型を使う場合は対応する mod 型を include する

using H = hash<long long, 2>; // long long で 2 本

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
