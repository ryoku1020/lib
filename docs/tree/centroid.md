---
title: Centroid Decomposition
documentation_of: ../../tree/centroid.hpp
---

# Centroid Decomposition

重心分解を再帰的に行い、その過程でコールバックを呼び出すための関数です。
通常の重心が選ばれた場合と、分解途中で仮想頂点として扱われた重心が選ばれた場合で別々のコールバックを受け取ります。

## `centroid_decomposition13`

### 使い方

```cpp
#include "tree/centroid.hpp"

vector<vector<int>> g(n);

auto call_nonvirtual=[&](int centroid,vector<vector<int>>&send,vector<int>&is_virtual){
    // 通常の重心に対する処理
};
auto call_virtual=[&](int centroid,vector<int>&col,vector<vector<int>>&send,vector<int>&is_virtual){
    // 仮想頂点になった重心に対する処理
};

centroid_decomposition13(g,call_nonvirtual,call_virtual);
```

例えば各重心で「その連結成分の頂点たちを DFS 順に受け取りたい」なら `send` をその場で走査します。

```cpp
auto call_nonvirtual=[&](int cen,vector<vector<int>>&send,vector<int>&is_virtual){
    vector<int> vs;
    auto dfs=[&](auto&dfs,int u,int p)->void{
        vs.push_back(u);
        for(int to:send[u]){
            if(to==p)continue;
            dfs(dfs,to,u);
        }
    };
    dfs(dfs,cen,-1);
};
```

### 引数

- `vvc<int>& g`
  隣接リストで表現された木です。処理中に一時的に書き換えられるため、参照で受け取ります。
- `F1& callnonvirtual`
  通常の重心が見つかったときに呼ばれるコールバックです。
  シグネチャは `void(int centroid,vvc<int>& send,vc<int>& is_virtual)` を想定しています。
- `F2& Callvirutal`
  仮想頂点として扱われる重心に対して呼ばれるコールバックです。
  シグネチャは `void(int centroid,vc<int>& col,vvc<int>& send,vc<int>& is_virtual)` を想定しています。

### `send`

各コールバックに渡される `send` は、その時点の連結成分を DFS した際に使われた辺を保持した隣接リストです。
コールバック終了後に内部でクリアされるので、必要ならその場で利用します。

### `col`

`Callvirutal` に渡される `col[u]` は、仮想頂点の重心を境にして頂点がどちら側の部分に属するかを表します。
値は 0 または 1 で、同じ側に属する頂点どうしが同じ値になります。

### オーバーロード

- `template<class tree,class F1,class F2> void centroid_decomposition13(tree& g,F1& callnonvirtual,F2& Callvirutal)`
  `g[i]` から `.to` を持つ辺を列挙できる木構造を受け取る版です。内部で `vector<vector<int>>` に変換してから同じ処理を行います。

### 境界・注意

- 実装中のコメントにもある通り、木やコールバックを copy して受け取ると意図しない動作になる可能性があります。参照で渡す前提です。
- 木であることを仮定しています。連結でないグラフやサイクルを含むグラフには使えません。
- コールバックのシグネチャが少し特殊なので、まずは `auto` ラムダで受けるのが安全です。

## 使用例

各重心が選ばれた順番を記録します。

```cpp
vvc<int> g(n);
// 辺を追加

vc<int> order;
auto call_nonvirtual=[&](int cen,vvc<int>& send,vc<int>& is_virtual){
    order.pb(cen);
};
auto call_virtual=[&](int cen,vc<int>& col,vvc<int>& send,vc<int>& is_virtual){
    order.pb(cen);
};

centroid_decomposition13(g,call_nonvirtual,call_virtual);
```
