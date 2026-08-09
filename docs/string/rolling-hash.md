---
title: RollingHash
documentation_of: ../../string/rolling-hash.hpp
---

# RollingHash

`Mod261Int` と `Hash` を使うローリングハッシュです。

```cpp
#include "math/mod261.hpp"
#include "string/rolling-hash.hpp"

RollingHash<> rh(s);
auto h=rh.get(l,r); // [l,r)
```

`RollingHash<N>` とすると `N` 本の base を並列に使い、返り値は
`Hash<Mod261Int,N>` になります。

## 静的メソッド

- `pow(n)` — `base^n`
- `ipow(n)` — `base^{-n}`

どちらも必要な次数まで内部の静的キャッシュを自動で拡張します。
