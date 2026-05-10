---
title: Monge
documentation_of: ../monge.hpp
---

# Monge

Monge 性を持つ行列・関数に対するアルゴリズムの詰め合わせです。

## `monotone_minima`

```cpp
template<class T, class F>
vector<T> monotone_minima(F& a, int h, int w);
```

各行の最小値を `O(h + w log h)` で求めます。

- `a(i, j)` — 行 `i`、列 `j` の値を返す関数。`a` が Monge 行列（または totally monotone matrix）であることが前提。
- `h` — 行数
- `w` — 列数
- 返り値: 長さ `h` の配列。`res[i]` = 行 `i` の最小値。

- 計算量: `O(h + w log h)`

### 使用例

```cpp
auto a = [&](int i, int j) -> long long {
    return cost[i][j]; // Monge 性を満たすコスト
};
auto res = monotone_minima<long long>(a, h, w);
// res[i] = i 行の最小コスト
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
- `inf` — 辺の重みの上界目安
- 返り値: 頂点 0 から頂点 n-1 へちょうど `d` 本の辺を使う最短路長

- 計算量: `O(n log^2 n log(MAX_WEIGHT))`

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

- 計算量: `O(n log^2 n)`

## 注意

- いずれの関数も `f(i, j)` の定義域は `i < j` です。
- Monge 性（四辺形不等式）が成立しない場合、結果は保証されません。
- `monge_d_edge_shortest` の精度は `inf` パラメータに依存します。コスト上界より十分大きい値を渡してください。
