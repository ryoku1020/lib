---
title: Monge
documentation_of: ../monge.hpp
---

# Monge

Monge性を持つ行列や関数に対するアルゴリズムの詰め合わせです。

## monotone_minima

```cpp
template<class T, class F>
vector<T> monotone_minima(F& a, int h, int w, int ismax = 0);
```
Monotone Minimaを用いて、各行の最小値を求めます。
関数 $f(i, j)$ が Monge 性を満たすとき、各行 $i$ ($0 \le i < h$) について $f(i, j)$ を最小にする列 $j$ を効率よく探します。

### 制約・引数
- `F& a`: `a(i, j)` で $(i, j)$ の値を返す関数オブジェクト
- `int h`: 行の数
- `int w`: 列の数
- `int ismax`: 現在未使用

### 戻り値
- 各行の最小値を格納した `vector<T>` 型の配列

### 計算量
- $O(h + w \log h)$

## monge_d_edge_shortest

```cpp
template<class F>
ll monge_d_edge_shortest(F& f, int n, int d, ll inf = 2e13);
```
Alien DP (WQS二分探索) と分割統治法(Divide and Conquer DP / Monotone Minima)を組み合わせた、Mongeグラフ上の辺数指定最短路問題を解く関数です。
$0$ から $n-1$ まで、ちょうど $d$ 本の辺を使って移動する際の最短経路長を求めます。

### 制約・引数
- `F& f`: `f(i, j)` で $i$ から $j$ ($i < j$) への辺の重みを返す関数オブジェクト。辺の重みはMonge性を満たす必要があります。
- `int n`: 頂点数。頂点番号は $0$ から $n-1$ まで。
- `int d`: 使用する辺の数
- `ll inf`: 無限大を表す値

### 計算量
- $O(n \log^2 n \log(\text{MAX\_WEIGHT}))$

## monge_edge_shortest2

```cpp
template<class F>
pair<ll, ll> monge_edge_shortest2(F& f, int n);
```
分割統治法とMonotone Minimaを用いた、Mongeグラフ上の最短路問題を解く関数です。
辺数に制限はなく、$0$ から $n-1$ までの最短経路長とその際に用いた辺数のペアを返します。

### 制約・引数
- `F& f`: `f(i, j)` で $i$ から $j$ ($i < j$) への辺の重みを返す関数オブジェクト。辺の重みはMonge性を満たす必要があります。
- `int n`: 頂点数。頂点番号は $0$ から $n-1$ まで。

### 戻り値
- `pair<ll, ll>`: (最短経路長, その経路で使った辺の数)

### 計算量
- $O(n \log^2 n)$
