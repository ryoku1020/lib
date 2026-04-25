---
title: Compress
documentation_of: ../../ds/compress.hpp
---

# Compress

座標圧縮ユーティリティです。

このページが参照している `ds/compress.hpp` はワークツリー上では見当たりませんが、利用箇所からは次のような API を想定していることが分かります。

## 想定される API

- `push(x)`
- `work()`
- `find(x)`
- `size()`
- `v`
  復元用の元値配列

## 利用イメージ

```cpp
Compress<long long> cp;
cp.push(x);
cp.push(y);
cp.work();
int id=cp.find(x);
auto orig=cp.v[id];
```

定義ファイルが追加されたら、このページも実装に合わせて詰める想定です。
