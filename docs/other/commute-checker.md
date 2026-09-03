---
title: commute-checker
documentation_of: ../../other/commute-checker.hpp
---

# commute-checker

対応する `other/commute-checker.hpp` は現在空ファイルです。

## 状態

- 実装はまだ入っていません
- そのため公開 API もありません

将来実装が追加されたら、このページもそれに合わせて更新する想定です。

## 境界・注意

- 現時点では include しても利用できる API はありません。
- 可換性フラグを検出したい用途には、代替として `ds/utility/famous.hpp` の `famous_has_commute<T>::value` を利用できます。

## 計算量

`other/commute-checker.hpp` は空であり、利用可能な実装としての時間計算量・空間計算量は定義されません。

代替の `famous_has_commute<T>` はコンパイル時の型特性で、実行時処理はありません。

## 使用例（代替 API）

空の `commute-checker.hpp` 自体には使用例を示せません。可換な演算型かを調べるだけなら、次の代替を使えます。

```cpp
#include "ds/utility/famous.hpp"

static_assert(famous_has_commute<Sum<long long>>::value);
static_assert(!famous_has_commute<affine<long long>>::value);
```
