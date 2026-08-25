---
title: rolling_hash
documentation_of: ../../string/rolling-hash.hpp
---

# rolling_hash

`mod261_int` と `hash` を使うローリングハッシュです。

```cpp
#include "math/modular/mod261.hpp"
#include "string/rolling-hash.hpp"

rolling_hash<> rh(s);
auto h=rh.get(l,r); // [l,r)
```

`rolling_hash<N>` とすると `N` 本の base を並列に使い、返り値は
`hash<mod261_int,N>` になります。

## 静的メソッド

- `pow(n)` — `base^n`
- `ipow(n)` — `base^{-n}`

どちらも必要な次数まで内部の静的キャッシュを自動で拡張します。
