---
title: Monge
documentation_of: ../monge.hpp
---

# Monge

Monge 性を持つ行列・関数に対するアルゴリズムの詰め合わせです。

## `monotone_minima`

```cpp
template<class T, class F>
vector<T> monotone_minima(F& a, int h, int w, int ismax = 0);
```

各行の最小値を `O(h + w log h)` で求めます。

- `a(i, j)` — 行 `i`、列 `j` の値を返す関数。`a` が Monge 行列（または totally monotone matrix）であることが前提。
- `h` — 行数
- `w` — 列数
- 返り値: 長さ `h` の配列。`res[i]` = 行 `i` の最小値。
- `ismax` — 現行実装では参照されません。`1` を渡しても最大値計算にはなりません。

- 計算量: `O(h + w log h)`

### 使用例

```cpp
using P=pair<ll,int>;
auto a=[&](int i,int j)->P{
    return {cost[i][j],j}; // 値と argmin。cost は Monge 性を満たす
};
auto res=monotone_minima<P>(a,h,w);
// res[i].first: i 行の最小値、res[i].second: その列
```

---

## `monge_d_edge_shortest`

```cpp
template<class F>
ll monge_d_edge_shortest(F& f, int n, int d, ll inf = 2e13);
```

Alien DP（WQS 二分探索）と分割統治 DP（Monotone Minima）を組み合わせた、
Monge グラフ上でちょうど `d` 本の辺を使う最短路問題を解きます。

- `f(i, j)` — `i → j`（`i < j`）の辺重みを返す関数。Monge 性が必要。
- `n` — 頂点数（`0` から `n-1`）
- `d` — 使う辺の本数（ちょうど `d` 本）
- `inf` — WQS 二分探索で使うペナルティ探索幅
- 返り値: 頂点 0 から頂点 n-1 へちょうど `d` 本の辺を使う最短路長

- 計算量: `O(n log^2 n log(inf))` 時間、`O(n)` 補助領域

---

## `monge_edge_shortest2`

```cpp
template<class F>
pair<ll, ll> monge_edge_shortest2(F& f, int n);
```

辺数制限なしで Monge グラフ上の最短路と使用辺数を求めます。

- `f(i, j)` — `i → j`（`i < j`）の辺重み。Monge 性が必要。
- `n` — 頂点数（`0` から `n-1`）
- 返り値: `{最短路長, 使用辺数}`

- 計算量: `O(n log^2 n)` 時間、`O(n)` 補助領域

## 境界・注意

- `monotone_minima` は `h==0` なら空配列を返します。`h>0` では `w>0` が必要です。
- `monotone_minima` の初期値は `T` を 2 要素から構築するコードになっているため、現行実装は `pair<ll,int>` のような pair-like な `T` を想定しています。上記のようにスカラー値と列番号を組にしてください。`T=long long` ではコンパイルできません。
- 最小列番号が行とともに単調非減少になること、および `T` が `<` で比較できることを仮定します。`a` は非 const lvalue reference で受けるため、名前を付けたラムダや関数オブジェクトを渡してください。
- 2 つの最短路関数では `f(i,j)` の定義域を `i<j` とします。`monotone_minima` の `a(i,j)` は通常の `0<=i<h`, `0<=j<w` です。
- Monge 性（四辺形不等式）が成立しない場合、結果は保証されません。
- `monge_d_edge_shortest` は `n>=1`, `0<=d<=n-1`, `inf>0` を想定します。`inf` は WQS 二分探索のペナルティ探索区間 `[-inf,inf]` が最適な境界を含むほど十分大きくしてください。
- `monge_edge_shortest2` も `n>=1` が必要です。
- `ll` の内部番兵 `1e18` と加減算を使うため、辺重み、DP 値、ペナルティ計算が `ll` の範囲に収まり、有限な最適値が番兵より十分小さい必要があります。

## 使用例: Monge グラフの最短路

```cpp
auto cost=[&](int i,int j)->long long{
    assert(i<j);
    return (long long)(j-i)*(j-i)+w[j];
};

auto [dist,edges]=monge_edge_shortest2(cost,n);
```
