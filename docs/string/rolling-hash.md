---
title: rolling_hash
documentation_of: ../../string/rolling-hash.hpp
---

# rolling_hash

`2^61-1` を法とする `mod261_int` を使い、列の部分区間ハッシュを取得します。
`rolling_hash<N>` とすると独立な `N` 本のランダムな base を並列に使い、ハッシュ型は `hash_type<mod261_int,N>` になります。

## 構築とメソッド

### `rolling_hash<N> rh(const Container& s)`

列 `s` の prefix hash を構築します。要素は `long long` を経由して `mod261_int` に変換できる型を想定しています。

### `void rh.build(const Container& s)`

既存のオブジェクトを列 `s` で再構築します。長さ 0 の列も構築できます。

### `H rh.get(int l, int r) const`

半開区間 `s[l,r)` のハッシュを、区間の先頭が 0 次になるよう正規化して返します。
同じ長さの 2 区間は、開始位置が異なっても内容が同じなら同じ値になります。

### `static H rolling_hash<N>::add(H hash, int len, const H& x)`

長さ `len` の列を表す `hash` の末尾に 1 要素 `x` を追加したハッシュを返します。

### `static H rolling_hash<N>::pow(int n)` / `ipow(int n)`

`base^n` / `base^(-n)` を返します。必要な次数まで、`N` ごとの静的キャッシュを自動で拡張します。

## 計算量

列長を `n`、並列数を `N` とします。

- 構築・`build`: 時間 `O(Nn)`、オブジェクトのメモリ `O(Nn)`
- `get`, `add`: 時間 `O(N)`、追加メモリ `O(N)`（返り値）
- `pow(k)`, `ipow(k)`: 既にキャッシュ済みなら `O(1)` 参照。最大計算済み次数から `k` までの拡張は時間・静的メモリともに `O(Nk)` 累積

通常は `N` を小さい定数として、構築 `O(n)`・区間取得 `O(1)` とみなします。

## 境界・注意

- `get(l,r)` は `0 <= l <= r <= s.size()` を要求します（`assert` あり）。空区間のハッシュは 0 です。
- 構築する列の長さは `int` に収まる必要があります。
- デフォルト構築直後は `sum` が空なので `get` できません。空列を扱う場合も `build` を呼んでください。
- `pow(n)`, `ipow(n)`, `add(hash,len,x)` の次数・長さは非負でなければなりません。
- ハッシュ一致は文字列一致の必要条件であり、衝突確率は 0 ではありません。重要な判定では `N=2` 以上や、必要に応じた実データ比較を使ってください。
- base はプロセスごとにランダムに選ばれるため、実行をまたいだ永続 ID やシリアライズ値には使えません。
- 長さの異なる列や、値 0 を含む列をハッシュだけで比較すると長さ情報が失われます。長さも併せて比較してください。
- 累乗キャッシュは同じ `N` の全インスタンスで共有され、最大長まで保持されます。

## 使用例

```cpp
#include "string/rolling-hash.hpp"

string s="abracadabra";
rolling_hash<2> rh(s);

// s[0,4) と s[7,11) はどちらも "abra"
bool same=rh.get(0,4)==rh.get(7,11);

// 空区間も取得できる
auto empty_hash=rh.get(3,3);
```
